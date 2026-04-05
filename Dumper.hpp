#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

namespace IL2CPP
{
    namespace Dumper
    {
        static uintptr_t GetModuleBase()
        {
            std::ifstream maps("/proc/self/maps");
            std::string line;
            while (std::getline(maps, line))
            {
                if (line.find("libil2cpp.so") != std::string::npos && line.find("r-xp") != std::string::npos)
                {
                    return strtoull(line.c_str(), nullptr, 16);
                }
            }
            return 0;
        }

        static std::string GetTypeName(Unity::il2cppType* m_pType)
        {
            if (!m_pType) return "void";

            switch (m_pType->type)
            {
                case Unity::IL2CPP_TYPE_VOID:    return "void";
                case Unity::IL2CPP_TYPE_BOOLEAN: return "bool";
                case Unity::IL2CPP_TYPE_CHAR:    return "char";
                case Unity::IL2CPP_TYPE_I1:      return "sbyte";
                case Unity::IL2CPP_TYPE_U1:      return "byte";
                case Unity::IL2CPP_TYPE_I2:      return "short";
                case Unity::IL2CPP_TYPE_U2:      return "ushort";
                case Unity::IL2CPP_TYPE_I4:      return "int";
                case Unity::IL2CPP_TYPE_U4:      return "uint";
                case Unity::IL2CPP_TYPE_I8:      return "long";
                case Unity::IL2CPP_TYPE_U8:      return "ulong";
                case Unity::IL2CPP_TYPE_R4:      return "float";
                case Unity::IL2CPP_TYPE_R8:      return "double";
                case Unity::IL2CPP_TYPE_STRING:  return "string";
                case Unity::IL2CPP_TYPE_OBJECT:  return "object";
                default:
                {
                    Unity::il2cppClass* m_pClass = Class::Utils::ClassFromType(m_pType);
                    if (m_pClass && m_pClass->name)
                    {
                        std::string m_sName;
                        if (m_pClass->namespaze && m_pClass->namespaze[0] != '\0')
                        {
                            m_sName += m_pClass->namespaze;
                            m_sName += '.';
                        }
                        m_sName += m_pClass->name;
                        return m_sName;
                    }
                    return "unknown";
                }
            }
        }

        static std::string GetFieldTypeName(Unity::il2cppType* m_pType)
        {
            std::string m_sName = GetTypeName(m_pType);
            if (m_pType->byref) m_sName += "&";
            return m_sName;
        }

        static std::string GetAccessModifier(uint32_t m_uFlags, bool m_bIsField)
        {
            uint32_t m_uMask = m_bIsField
                ? Unity::FIELD_ATTRIBUTE_FIELD_ACCESS_MASK
                : Unity::METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;

            uint32_t m_uAccess = m_uFlags & m_uMask;
            if (m_uAccess == Unity::FIELD_ATTRIBUTE_PRIVATE || m_uAccess == Unity::METHOD_ATTRIBUTE_PRIVATE)
                return "private";
            if (m_uAccess == Unity::FIELD_ATTRIBUTE_FAMILY || m_uAccess == Unity::METHOD_ATTRIBUTE_FAMILY)
                return "protected";
            if (m_uAccess == Unity::FIELD_ATTRIBUTE_PUBLIC || m_uAccess == Unity::METHOD_ATTRIBUTE_PUBLIC)
                return "public";
            if (m_uAccess == Unity::FIELD_ATTRIBUTE_ASSEMBLY || m_uAccess == Unity::METHOD_ATTRIBUTE_ASSEM)
                return "internal";
            return m_bIsField ? "private" : "public";
        }

        static std::string GetClassVisibility(uint32_t m_uFlags)
        {
            switch (m_uFlags & Unity::TYPE_ATTRIBUTE_VISIBILITY_MASK)
            {
                case Unity::TYPE_ATTRIBUTE_PUBLIC:
                case Unity::TYPE_ATTRIBUTE_NESTED_PUBLIC:
                    return "public";
                case Unity::TYPE_ATTRIBUTE_NESTED_PRIVATE:
                    return "private";
                case Unity::TYPE_ATTRIBUTE_NESTED_FAMILY:
                    return "protected";
                case Unity::TYPE_ATTRIBUTE_NESTED_ASSEMBLY:
                    return "internal";
                default:
                    return "internal";
            }
        }

        static std::string GetClassType(Unity::il2cppClass* m_pClass, uint32_t m_uFlags)
        {
            if (m_uFlags & Unity::TYPE_ATTRIBUTE_INTERFACE)
                return "interface";

            if (Class::IsEnum(m_pClass))
                return "enum";

            if (Class::IsValueType(m_pClass))
                return "struct";

            if (m_uFlags & Unity::TYPE_ATTRIBUTE_SEALED)
                return "sealed class";

            return "class";
        }

        static std::string GetParentName(Unity::il2cppClass* m_pClass)
        {
            Unity::il2cppClass* m_pParent = Class::GetParent(m_pClass);
            if (!m_pParent || !m_pParent->name) return "";

            std::string m_sParent = m_pParent->name;
            if (strcmp(m_sParent.c_str(), "System.Object") == 0 ||
                strcmp(m_sParent.c_str(), "System.ValueType") == 0 ||
                strcmp(m_sParent.c_str(), "System.Enum") == 0 ||
                strcmp(m_sParent.c_str(), "System.MulticastDelegate") == 0 ||
                strcmp(m_sParent.c_str(), "System.Delegate") == 0)
                return "";

            if (m_pParent->namespaze && m_pParent->namespaze[0] != '\0')
            {
                std::string m_sFull;
                m_sFull += m_pParent->namespaze;
                m_sFull += '.';
                m_sFull += m_pParent->name;
                return m_sFull;
            }

            return m_sParent;
        }

        static void Dump()
        {
            Unity::System_String* m_pPath = Unity::Application::PersistentDataPath();
            if (!m_pPath) return;

            std::string m_sPath = m_pPath->ToString();
            m_sPath += "/dump.cs";

            std::ofstream m_File(m_sPath);
            if (!m_File.is_open()) return;

            size_t m_uAsmCount = 0;
            Unity::il2cppAssembly** m_pAssemblies = Domain::GetAssemblies(&m_uAsmCount);
            if (!m_pAssemblies || m_uAsmCount == 0) return;

            uintptr_t m_uBase = GetModuleBase();

            struct ImageInfo
            {
                const char* m_pName;
                size_t m_uClassCount;
            };
            std::vector<ImageInfo> m_vImages;

            for (size_t i = 0; i < m_uAsmCount; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->image) continue;

                const char* m_pImageName = m_pAssembly->image->name;
                if (!m_pImageName) m_pImageName = m_pAssembly->image->nameNoExt;
                if (!m_pImageName) continue;

                size_t m_uClassCount = reinterpret_cast<size_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ImageGetClassCount)(m_pAssembly->image);

                m_vImages.push_back({ m_pImageName, m_uClassCount });

                m_File << "// Image " << i << ": " << m_pImageName << " - " << m_uClassCount << std::endl;
            }

            m_File << std::endl;

            for (size_t i = 0; i < m_uAsmCount; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->image) continue;

                size_t m_uClassCount = reinterpret_cast<size_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ImageGetClassCount)(m_pAssembly->image);

                for (size_t c = 0; c < m_uClassCount; ++c)
                {
                    Unity::il2cppClass* m_pClass = reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*, size_t)>(Functions.m_ImageGetClass)(m_pAssembly->image, c);
                    if (!m_pClass || !m_pClass->name) continue;

                    uint32_t m_uFlags = reinterpret_cast<uint32_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassGetFlags)(m_pClass);

                    const char* m_pNamespace = m_pClass->namespaze ? m_pClass->namespaze : "";
                    std::string m_sVisibility = GetClassVisibility(m_uFlags);
                    std::string m_sClassType = GetClassType(m_pClass, m_uFlags);
                    std::string m_sClassName = m_pClass->name;
                    std::string m_sParent = GetParentName(m_pClass);

                    m_File << "// Namespace: " << m_pNamespace << std::endl;
                    m_File << m_sVisibility << " " << m_sClassType << " " << m_sClassName;
                    if (!m_sParent.empty())
                        m_File << " : " << m_sParent;
                    m_File << std::endl;
                    m_File << "{" << std::endl;

                    bool m_bHasFields = false;
                    bool m_bHasMethods = false;

                    void* m_pFieldIter = nullptr;
                    std::vector<Unity::il2cppFieldInfo*> m_vFields;
                    while (1)
                    {
                        Unity::il2cppFieldInfo* m_pField = Class::GetFields(m_pClass, &m_pFieldIter);
                        if (!m_pField) break;
                        m_vFields.push_back(m_pField);
                    }

                    if (!m_vFields.empty())
                    {
                        m_bHasFields = true;
                        m_File << "\t// Fields" << std::endl;

                        for (auto* m_pField : m_vFields)
                        {
                            std::string m_sAccess = GetAccessModifier(m_pField->type->attrs, true);
                            std::string m_sType = GetFieldTypeName(m_pField->type);
                            bool m_bStatic = (m_pField->type->attrs & Unity::FIELD_ATTRIBUTE_STATIC) != 0;

                            m_File << "\t" << m_sAccess;
                            if (m_bStatic) m_File << " static";
                            m_File << " " << m_sType << " " << m_pField->name;
                            if (!m_bStatic && m_pField->offset >= 0)
                                m_File << "; // 0x" << std::hex << m_pField->offset << std::dec;
                            else
                                m_File << ";";
                            m_File << std::endl;
                        }
                    }

                    void* m_pMethodIter = nullptr;
                    std::vector<Unity::il2cppMethodInfo*> m_vMethods;
                    while (1)
                    {
                        Unity::il2cppMethodInfo* m_pMethod = Class::GetMethods(m_pClass, &m_pMethodIter);
                        if (!m_pMethod) break;
                        m_vMethods.push_back(m_pMethod);
                    }

                    if (!m_vMethods.empty())
                    {
                        if (m_bHasFields) m_File << std::endl;
                        m_bHasMethods = true;
                        m_File << "\t// Methods" << std::endl;

                        for (auto* m_pMethod : m_vMethods)
                        {
                            if (!m_pMethod->methodPointer) continue;

                            uintptr_t m_uRVA = reinterpret_cast<uintptr_t>(m_pMethod->methodPointer) - m_uBase;
                            uintptr_t m_uVA = reinterpret_cast<uintptr_t>(m_pMethod->methodPointer);

                            const char* m_pMethodName = Class::Utils::MethodGetName(m_pMethod);
                            if (!m_pMethodName) m_pMethodName = "unknown";

                            uint32_t m_uMethodFlags = reinterpret_cast<uint32_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodGetFlags)(m_pMethod);
                            std::string m_sAccess = GetAccessModifier(m_uMethodFlags, false);
                            bool m_bStatic = (m_uMethodFlags & Unity::METHOD_ATTRIBUTE_STATIC) != 0;
                            bool m_bIsGeneric = Class::Utils::MethodIsGeneric(m_pMethod);

                            Unity::il2cppType* m_pReturnType = Class::Utils::MethodGetReturnType(m_pMethod);
                            std::string m_sReturnType = GetTypeName(m_pReturnType);

                            uint32_t m_uParamCount = Class::Utils::MethodGetParamCount(m_pMethod);

                            m_File << std::endl;
                            m_File << "\t// RVA: 0x" << std::hex << m_uRVA << " Offset: 0x" << m_uRVA << " VA: 0x" << m_uVA << std::dec << std::endl;
                            m_File << "\t" << m_sAccess;
                            if (m_bStatic) m_File << " static";
                            m_File << " " << m_sReturnType << " " << m_pMethodName << "(";

                            for (uint32_t p = 0; p < m_uParamCount; ++p)
                            {
                                Unity::il2cppType* m_pParamType = Class::Utils::GetMethodParamType(m_pMethod, p);
                                std::string m_sParamType = GetTypeName(m_pParamType);
                                const char* m_pParamName = Class::Utils::MethodGetParamName(m_pMethod, p);
                                if (!m_pParamName) m_pParamName = "";

                                if (p > 0) m_File << ", ";
                                m_File << m_sParamType << " " << m_pParamName;
                            }

                            m_File << ") { }" << std::endl;
                        }
                    }

                    m_File << "}" << std::endl << std::endl;
                }
            }

            m_File.close();
        }
    }
}
