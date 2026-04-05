#pragma once

#include <type_traits>
#include <cstdio>

namespace IL2CPP
{
    namespace Class
    {
        Unity::il2cppFieldInfo* GetFields(Unity::il2cppClass* m_pClass, void** m_pIterator)
        {
            return reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, void**)>(Functions.m_ClassGetFields)(m_pClass, m_pIterator);
        }

        void FetchFields(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator = nullptr)
        {
            m_pVector->clear();

            while (1)
            {
                Unity::il2cppFieldInfo* m_pField = GetFields(m_pClass, &m_pFieldIterator);
                if (!m_pField)
                    break;

                m_pVector->emplace_back(m_pField);
            }
        }

        Unity::il2cppMethodInfo* GetMethods(Unity::il2cppClass* m_pClass, void** m_pIterator)
        {
            return reinterpret_cast<Unity::il2cppMethodInfo * (IL2CPP_CALLING_CONVENTION)(void*, void**)>(Functions.m_ClassGetMethods)(m_pClass, m_pIterator);
        }

        void FetchMethods(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator = nullptr)
        {
            m_pVector->clear();

            while (1)
            {
                Unity::il2cppMethodInfo* m_pMethod = GetMethods(m_pClass, &m_pMethodIterator);
                if (!m_pMethod)
                    break;

                m_pVector->emplace_back(m_pMethod);
            }
        }

        Unity::il2cppType* GetType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppType * (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassGetType)(m_pClass);
        }

        Unity::il2cppObject* GetSystemType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppObject * (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_TypeGetObject)(GetType(m_pClass));
        }

        Unity::il2cppClass* GetFromName(Unity::il2cppImage* m_pImage, const char* m_pNamespace, const char* m_pName)
        {
            return reinterpret_cast<Unity::il2cppClass * (IL2CPP_CALLING_CONVENTION)(void*, const char*, const char*)>(Functions.m_ClassFromName)(m_pImage, m_pNamespace, m_pName);
        }

        Unity::il2cppClass* Find(const char* m_pName)
        {
            size_t m_sAssembliesCount = 0U;
            Unity::il2cppAssembly** m_pAssemblies = Domain::GetAssemblies(&m_sAssembliesCount);
            if (!m_pAssemblies || 0U >= m_sAssembliesCount) return nullptr;

            const char* m_pNameSpaceEnd = strrchr(m_pName, '.');
            char* m_pNameSpace = nullptr;
            if (m_pNameSpaceEnd)
            {
                uintptr_t m_uNamespaceSize = static_cast<uintptr_t>(m_pNameSpaceEnd - m_pName);
                m_pNameSpace = new char[m_uNamespaceSize + 1];
                memcpy(m_pNameSpace, m_pName, m_uNamespaceSize);
                m_pNameSpace[m_uNamespaceSize] = '\0';

                m_pName = m_pNameSpaceEnd + 1;
            }
            else
            {
                m_pNameSpace = new char[2];
                memset(m_pNameSpace, 0, 2);
            }

            Unity::il2cppClass* m_pClassReturn = nullptr;
            for (size_t i = 0U; m_sAssembliesCount > i; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->image) continue;

                m_pClassReturn = GetFromName(m_pAssembly->image, m_pNameSpace, m_pName);
                if (m_pClassReturn) break;
            }

            delete[] m_pNameSpace;

            if (m_pClassReturn)
                printf("[Find] Found: %s\n", m_pName ? m_pName : "(null)");
            else
                printf("[Find] Not Found: %s\n", m_pName ? m_pName : "(null)");

            return m_pClassReturn;
        }

        Unity::il2cppObject* GetSystemType(const char* m_pClassName)
        {
            Unity::il2cppClass* m_pClass = Find(m_pClassName);
            if (!m_pClass)
                return nullptr;

            return GetSystemType(m_pClass);
        }

        void FetchClasses(std::vector<Unity::il2cppClass*>* m_pVector, const char* m_pModuleName, const char* m_pNamespace)
        {
            m_pVector->clear();

            size_t m_sAssembliesCount = 0U;
            Unity::il2cppAssembly** m_pAssemblies = Domain::GetAssemblies(&m_sAssembliesCount);
            if (!m_pAssemblies || 0U >= m_sAssembliesCount) return;

            Unity::il2cppImage* m_pImage = nullptr;
            for (size_t i = 0U; m_sAssembliesCount > i; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->image || strcmp(m_pAssembly->image->nameNoExt, m_pModuleName) != 0)
                    continue;

                m_pImage = m_pAssembly->image;
                break;
            }

            if (m_pImage)
            {
                size_t m_sClassesCount = reinterpret_cast<size_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ImageGetClassCount)(m_pImage);
                for (size_t i = 0U; m_sClassesCount > i; ++i)
                {
                    Unity::il2cppClass* m_pClass = reinterpret_cast<Unity::il2cppClass * (IL2CPP_CALLING_CONVENTION)(void*, size_t)>(Functions.m_ImageGetClass)(m_pImage, i);
                    if (m_pNamespace)
                    {
                        if (m_pNamespace[0] == '\0')
                        {
                            if (m_pClass->namespaze[0] != '\0')
                                continue;
                        }
                        else if (strcmp(m_pClass->namespaze, m_pNamespace) != 0)
                            continue;
                    }

                    m_pVector->emplace_back(m_pClass);
                }
            }
        }

        bool IsGeneric(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassIsGeneric)(m_pClass);
        }

        bool IsInflated(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassIsInflated)(m_pClass);
        }

        bool IsValueType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassIsValuetype)(m_pClass);
        }

        bool IsEnum(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassIsEnum)(m_pClass);
        }

        bool IsAssignableFrom(Unity::il2cppClass* m_pClass, Unity::il2cppClass* m_pFrom)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_ClassIsAssignableFrom)(m_pClass, m_pFrom);
        }

        bool IsSubclassOf(Unity::il2cppClass* m_pClass, Unity::il2cppClass* m_pKlass, bool m_bCheckInterfaces)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*, void*, bool)>(Functions.m_ClassIsSubclassOf)(m_pClass, m_pKlass, m_bCheckInterfaces);
        }

        Unity::il2cppClass* GetParent(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassGetParent)(m_pClass);
        }

        Unity::il2cppClass* GetDeclaringType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassGetDeclaringType)(m_pClass);
        }

        Unity::il2cppClass* ObjectGetClass(Unity::il2cppObject* m_pObject)
        {
            return reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ObjectGetClass)(m_pObject);
        }

        Unity::il2cppObject* ValueBox(Unity::il2cppClass* m_pClass, void* m_pData)
        {
            return reinterpret_cast<Unity::il2cppObject*(IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_ValueBox)(m_pClass, m_pData);
        }

        void* ObjectUnbox(Unity::il2cppObject* m_pObject)
        {
            return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ObjectUnbox)(m_pObject);
        }

        namespace Utils
        {
            int GetFieldOffset(Unity::il2cppClass* m_pClass, const char* m_pName)
            {
                void* m_pFieldIterator = nullptr;
                while (1)
                {
                    Unity::il2cppFieldInfo* m_pField = GetFields(m_pClass, &m_pFieldIterator);
                    if (!m_pField)
                        break;

                    if (strcmp(m_pField->name, m_pName) == 0)
                        return m_pField->offset;
                }

                return -1;
            }

            int GetFieldOffset(const char* m_pClassName, const char* m_pName)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetFieldOffset(m_pClass, m_pName);

                return -1;
            }

            void SetStaticField(Unity::il2cppClass* m_pClass, const char* m_pMemberName, void* m_pValue) {
                Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_pClass, m_pMemberName);
                if (m_pField)
                    reinterpret_cast<void (IL2CPP_CALLING_CONVENTION)(Unity::il2cppFieldInfo*, void*)>(Functions.m_FieldStaticSetValue)(m_pField, m_pValue);
            }

            void SetStaticField(const char* m_pClassName, const char* m_pMemberName, void* m_pValue) {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    SetStaticField(m_pClass, m_pMemberName, m_pValue);
            }

            void* GetStaticField(Unity::il2cppClass* m_pClass, const char* m_pMemberName) {
                Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_pClass, m_pMemberName);
                void* m_pValue = nullptr;
                if (m_pField)
                    reinterpret_cast<void (IL2CPP_CALLING_CONVENTION)(Unity::il2cppFieldInfo*, void*)>(Functions.m_FieldStaticGetValue)(m_pField, &m_pValue);

                return m_pValue;
            }

            void* GetStaticField(const char* m_pClassName, const char* m_pMemberName)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetStaticField(m_pClass, m_pMemberName);

                return nullptr;
            }

            void* GetMethodPointer(Unity::il2cppClass* m_pClass, const char* m_pMethodName, int m_iArgs = -1)
            {
                Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Functions.m_ClassGetMethodFromName)(m_pClass, m_pMethodName, m_iArgs);
                if (!pMethod)
                {
                    printf("[GetMethodPointer] Not Found: %s::%s\n",
                        (m_pClass && m_pClass->name) ? m_pClass->name : "(null)",
                        m_pMethodName ? m_pMethodName : "(null)");
                    return nullptr;
                }

                printf("[GetMethodPointer] Found: %s::%s\n",
                    (m_pClass && m_pClass->name) ? m_pClass->name : "(null)",
                    m_pMethodName ? m_pMethodName : "(null)");

                return pMethod->methodPointer;
            }

            void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, int m_iArgs = -1)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetMethodPointer(m_pClass, m_pMethodName, m_iArgs);

                printf("[GetMethodPointer] Not Found: class %s not found\n",
                    m_pClassName ? m_pClassName : "(null)");
                return nullptr;
            }

            uint32_t MethodGetParamCount(Unity::il2cppMethodInfo* m_pMethodInfo)
            {
                return reinterpret_cast<uint32_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodGetParamCount)(m_pMethodInfo);
            }

            const char* MethodGetName(Unity::il2cppMethodInfo* m_pMethodInfo)
            {
                return reinterpret_cast<const char*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodGetName)(m_pMethodInfo);
            }

            Unity::il2cppType* MethodGetReturnType(Unity::il2cppMethodInfo* m_pMethodInfo)
            {
                return reinterpret_cast<Unity::il2cppType*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodGetReturnType)(m_pMethodInfo);
            }

            const char* MethodGetParamName(Unity::il2cppMethodInfo* m_pMethodInfo, uint32_t index)
            {
                if (index >= MethodGetParamCount(m_pMethodInfo))
                    return nullptr;

                return reinterpret_cast<const char * (IL2CPP_CALLING_CONVENTION)(void*, uint32_t)>(Functions.m_MethodGetParamName)(m_pMethodInfo, index);
            }

            Unity::il2cppType* GetMethodParamType(Unity::il2cppMethodInfo* m_pMethodInfo, uint32_t index) {
                if (index >= MethodGetParamCount(m_pMethodInfo))
                    return nullptr;

                return reinterpret_cast<Unity::il2cppType * (IL2CPP_CALLING_CONVENTION)(void*, uint32_t)>(Functions.m_MethodGetParam)(m_pMethodInfo, index);
            }

            Unity::il2cppClass* ClassFromType(Unity::il2cppType * type)
            {
                return reinterpret_cast<Unity::il2cppClass * (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassFromIl2cppType)(type);
            }

            void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, std::initializer_list<const char*> m_vNames)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (!m_pClass)
                {
                    printf("[GetMethodPointer] Not Found: class %s not found\n",
                        m_pClassName ? m_pClassName : "(null)");
                    return nullptr;
                }

                int m_iNamesCount = static_cast<int>(m_vNames.size());
                const char** m_pNames = const_cast<const char**>(m_vNames.begin());

                void* m_pMethodIterator = nullptr;
                while (1)
                {
                    Unity::il2cppMethodInfo* m_pMethod = GetMethods(m_pClass, &m_pMethodIterator);
                    if (!m_pMethod)
                        break;

                    if (strcmp(MethodGetName(m_pMethod), m_pMethodName) != 0)
                        continue;

                    bool m_bParamsMatch = true;
                    for (int i = 0; m_iNamesCount > i; ++i)
                    {
                        Unity::il2cppType* m_pParamType = GetMethodParamType(m_pMethod, static_cast<uint32_t>(i));
                        if (!m_pParamType) { m_bParamsMatch = false; break; }
                        Unity::il2cppClass* m_pParamClass = ClassFromType(m_pParamType);
                        if (!m_pParamClass || strcmp(m_pParamClass->name, m_pNames[i]) != 0) { m_bParamsMatch = false; break; }
                    }
                    if (m_bParamsMatch)
                    {
                        printf("[GetMethodPointer] Found: %s::%s\n",
                            m_pClassName ? m_pClassName : "(null)",
                            m_pMethodName ? m_pMethodName : "(null)");
                        return m_pMethod->methodPointer;
                    }
                }

                printf("[GetMethodPointer] Not Found: %s::%s\n",
                    m_pClassName ? m_pClassName : "(null)",
                    m_pMethodName ? m_pMethodName : "(null)");
                return nullptr;
            }

            Unity::il2cppClass* FilterClass(std::vector<Unity::il2cppClass*>* m_pClasses, std::initializer_list<const char*> m_vNames, int m_iFoundCount = -1)
            {
                int m_iNamesCount = static_cast<int>(m_vNames.size());
                const char** m_pNames = const_cast<const char**>(m_vNames.begin());

                if (0 >= m_iFoundCount || m_iFoundCount > m_iNamesCount)
                    m_iFoundCount = m_iNamesCount;

                Unity::il2cppClass* m_pReturn = nullptr;
                for (size_t c = 0; m_pClasses->size() > c; ++c)
                {
                    int m_iFoundCountNow = 0;

                    Unity::il2cppClass* m_pClass = m_pClasses->operator[](c);
                    if (!m_pClass)
                        continue;

                    for (int i = 0; m_iNamesCount > i; ++i)
                    {
                        const char* m_pNameToFind = m_pNames[i];

                        bool m_bFoundInClass = false;
                        if (m_pNameToFind[0] == '~') // Field
                            m_bFoundInClass = GetFieldOffset(m_pClass, &m_pNameToFind[1]) >= 0;
                        else if (m_pNameToFind[0] == '-') // Method
                            m_bFoundInClass = GetMethodPointer(m_pClass, &m_pNameToFind[1]) != nullptr;
                        else // Both
                        {
                            m_bFoundInClass = GetFieldOffset(m_pClass, m_pNameToFind) >= 0;
                            if (!m_bFoundInClass)
                                m_bFoundInClass = GetMethodPointer(m_pClass, m_pNameToFind) != nullptr;
                        }

                        if (m_bFoundInClass)
                            ++m_iFoundCountNow;
                    }

                    if (m_iFoundCount == m_iFoundCountNow)
                    {
                        m_pReturn = m_pClass;
                        break;
                    }
                }

                return m_pReturn;
            }

            void* FilterClassToMethodPointer(std::vector<Unity::il2cppClass*>* m_pClasses, const char* m_pMethodName, int m_iArgs = -1)
            {
                void* m_pMethodPointer = nullptr;
                for (size_t c = 0; m_pClasses->size() > c; ++c)
                {
                    Unity::il2cppClass* m_pClass = m_pClasses->operator[](c);
                    if (!m_pClass)
                        continue;

                    m_pMethodPointer = GetMethodPointer(m_pClass, m_pMethodName, m_iArgs);
                    if (m_pMethodPointer)
                        break;
                }

                return m_pMethodPointer;
            }

            std::string GetFullTypeName(Unity::il2cppType* type)
            {
                if (!type) return "?";
                Unity::il2cppClass* klass = ClassFromType(type);
                if (!klass || !klass->name) return "?";
                std::string result;
                if (klass->namespaze && klass->namespaze[0] != '\0') {
                    result += klass->namespaze;
                    result += '.';
                }
                result += klass->name;
                return result;
            }

            bool MethodIsGeneric(Unity::il2cppMethodInfo* m_pMethod)
            {
                return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodIsGeneric)(m_pMethod);
            }

            bool MethodIsInflated(Unity::il2cppMethodInfo* m_pMethod)
            {
                return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodIsInflated)(m_pMethod);
            }

            bool MethodIsInstance(Unity::il2cppMethodInfo* m_pMethod)
            {
                return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodIsInstance)(m_pMethod);
            }

            bool IsInstanceOf(Unity::il2cppObject* m_pObject, Unity::il2cppClass* m_pClass)
            {
                if (!m_pObject || !m_pClass) return false;
                Unity::il2cppClass* m_pObjClass = reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ObjectGetClass)(m_pObject);
                if (!m_pObjClass) return false;
                return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_ClassIsAssignableFrom)(m_pClass, m_pObjClass);
            }

            Unity::il2cppObject* MakeGenericType(Unity::il2cppClass* m_pGenericClass, std::initializer_list<Unity::il2cppClass*> m_vTypeArgs)
            {
                Unity::il2cppObject* m_pSystemType = GetSystemType(m_pGenericClass);
                if (!m_pSystemType) return nullptr;

                Unity::il2cppClass* m_pTypeClass = Find("System.Type");
                if (!m_pTypeClass) return nullptr;

                Unity::il2cppClass* m_pTypeArrayClass = reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*, void*, uintptr_t)>(Functions.m_ArrayClassGet)(m_pTypeClass, reinterpret_cast<void*>(1), 0);
                if (!m_pTypeArrayClass) return nullptr;

                Unity::il2cppObject* m_pTypeArray = reinterpret_cast<Unity::il2cppObject*(IL2CPP_CALLING_CONVENTION)(void*, uintptr_t)>(Functions.m_ArrayNew)(m_pTypeArrayClass, m_vTypeArgs.size());
                if (!m_pTypeArray) return nullptr;

                uintptr_t m_pArrayBase = reinterpret_cast<uintptr_t>(m_pTypeArray) + sizeof(Unity::il2cppObject) + sizeof(uintptr_t) * 2;
                size_t m_iIdx = 0;
                for (Unity::il2cppClass* m_pArg : m_vTypeArgs)
                    reinterpret_cast<Unity::il2cppObject**>(m_pArrayBase)[m_iIdx++] = GetSystemType(m_pArg);

                void* m_pMakeGeneric = GetMethodPointer(m_pTypeClass, "MakeGenericType", 1);
                if (!m_pMakeGeneric) return nullptr;

                return reinterpret_cast<Unity::il2cppObject*(UNITY_CALLING_CONVENTION)(void*, void*)>(m_pMakeGeneric)(m_pSystemType, m_pTypeArray);
            }

            template<typename Ret, typename... Args>
            typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
            CallMethod(Unity::il2cppClass* m_pClass, const char* m_pMethodName, Args... args)
            {
                void* m_pPtr = GetMethodPointer(m_pClass, m_pMethodName, static_cast<int>(sizeof...(Args)));
                if (!m_pPtr) { Ret m_tDefault{}; return m_tDefault; }
                return reinterpret_cast<Ret(IL2CPP_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
            }

            template<typename Ret = void, typename... Args>
            typename std::enable_if<std::is_void<Ret>::value>::type
            CallMethod(Unity::il2cppClass* m_pClass, const char* m_pMethodName, Args... args)
            {
                void* m_pPtr = GetMethodPointer(m_pClass, m_pMethodName, static_cast<int>(sizeof...(Args)));
                if (!m_pPtr) return;
                reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
            }

            template<typename Ret, typename... Args>
            typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
            CallMethod(const char* m_pClassName, const char* m_pMethodName, Args... args)
            {
                void* m_pPtr = GetMethodPointer(m_pClassName, m_pMethodName, static_cast<int>(sizeof...(Args)));
                if (!m_pPtr) { Ret m_tDefault{}; return m_tDefault; }
                return reinterpret_cast<Ret(IL2CPP_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
            }

            template<typename Ret = void, typename... Args>
            typename std::enable_if<std::is_void<Ret>::value>::type
            CallMethod(const char* m_pClassName, const char* m_pMethodName, Args... args)
            {
                void* m_pPtr = GetMethodPointer(m_pClassName, m_pMethodName, static_cast<int>(sizeof...(Args)));
                if (!m_pPtr) return;
                reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
            }

            Unity::il2cppMethodInfo* MakeGenericMethod(Unity::il2cppMethodInfo* m_pGenericMethod, std::initializer_list<Unity::il2cppClass*> m_vTypeArgs)
            {
                if (!m_pGenericMethod) return nullptr;

                Unity::il2cppClass* m_pMethodInfoClass = Find("System.Reflection.MethodInfo");
                if (!m_pMethodInfoClass) return nullptr;

                Unity::il2cppClass* m_pTypeClass = Find("System.Type");
                if (!m_pTypeClass) return nullptr;

                Unity::il2cppObject* m_pMethodObj = reinterpret_cast<Unity::il2cppObject*(IL2CPP_CALLING_CONVENTION)(void*, void*)>(Functions.m_MethodGetObject)(m_pGenericMethod, reinterpret_cast<Unity::il2cppClass*>(m_pGenericMethod));
                if (!m_pMethodObj) return nullptr;

                Unity::il2cppClass* m_pTypeArrayClass = reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*, void*, uintptr_t)>(Functions.m_ArrayClassGet)(m_pTypeClass, reinterpret_cast<void*>(1), 0);
                if (!m_pTypeArrayClass) return nullptr;

                Unity::il2cppObject* m_pTypeArray = reinterpret_cast<Unity::il2cppObject*(IL2CPP_CALLING_CONVENTION)(void*, uintptr_t)>(Functions.m_ArrayNew)(m_pTypeArrayClass, m_vTypeArgs.size());
                if (!m_pTypeArray) return nullptr;

                uintptr_t m_pArrayBase = reinterpret_cast<uintptr_t>(m_pTypeArray) + sizeof(Unity::il2cppObject) + sizeof(uintptr_t) * 2;
                size_t m_iIdx = 0;
                for (Unity::il2cppClass* m_pArg : m_vTypeArgs)
                    reinterpret_cast<Unity::il2cppObject**>(m_pArrayBase)[m_iIdx++] = GetSystemType(m_pArg);

                void* m_pMakeGeneric = GetMethodPointer(m_pMethodInfoClass, "MakeGenericMethod", 1);
                if (!m_pMakeGeneric) return nullptr;

                Unity::il2cppObject* m_pResult = reinterpret_cast<Unity::il2cppObject*(UNITY_CALLING_CONVENTION)(void*, void*)>(m_pMakeGeneric)(m_pMethodObj, m_pTypeArray);
                if (!m_pResult) return nullptr;

                return reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_MethodGetFromReflection)(m_pResult);
            }
        }
    }

    enum class m_eClassPropType : int
    {
        Unknown = 0,
        Field,			// Member of class that can be accessed directly by RVA
        Property,		// Member of class that can be accessed by calling function
        Method,			// Function of class
    };

    // Main Class
    class CClass
    {
    public:
        Unity::il2cppObject m_Object;
        void* m_CachedPtr = nullptr;

        // Wrappers for namespace, ah...
        Unity::il2cppFieldInfo* GetFields(void** m_pIterator)
        {
            return Class::GetFields(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pIterator);
        }

        void FetchFields(std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator = nullptr)
        {
            Class::FetchFields(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pVector, m_pFieldIterator);
        }

        Unity::il2cppMethodInfo* GetMethods(void** m_pIterator)
        {
            return Class::GetMethods(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pIterator);
        }

        void FetchMethods(std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator = nullptr)
        {
            Class::FetchMethods(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pVector, m_pMethodIterator);
        }

        void* GetMethodPointer(const char* m_pMethodName, int m_iArgs = -1)
        {
            return Class::Utils::GetMethodPointer(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMethodName, m_iArgs);
        }

        m_eClassPropType GetPropType(const char* m_pPropType)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pPropType);
            if (pField)
                return m_eClassPropType::Field;

            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pPropType);
            if (pProperty)
                return m_eClassPropType::Property;

            Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Functions.m_ClassGetMethodFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pPropType, -1);
            if (pMethod)
                return m_eClassPropType::Method;

            return m_eClassPropType::Unknown;
        }
        
        // Properties/Fields

        template<typename T>
        T GetPropertyValue(const char* m_pPropertyName)
        {
            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pPropertyName);
            if (pProperty && pProperty->get)
                return reinterpret_cast<T(UNITY_CALLING_CONVENTION)(void*)>(reinterpret_cast<Unity::il2cppMethodInfo*>(pProperty->get)->methodPointer)(this);

            T tDefault = {};
            return tDefault;
        }

        template<typename T>
        void SetPropertyValue(const char* m_pPropertyName, T m_tValue)
        {
            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pPropertyName);
            if (pProperty && pProperty->set)
                return reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, T)>(reinterpret_cast<Unity::il2cppMethodInfo*>(pProperty->set)->methodPointer)(this, m_tValue);
        }

        template<typename T>
        __inline T GetMemberValue(int m_iOffset)
        {
            return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
        }

        template<typename T>
        __inline void SetMemberValue(int m_iOffset, T m_tValue)
        {
            *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset) = m_tValue;
        }

        template<typename T>
        __inline T GetMemberValue(Unity::il2cppFieldInfo* m_pField)
        {
            if (!m_pField || 0 > m_pField->offset)
            {
                T m_tDefault = {};
                return m_tDefault;
            }

            return GetMemberValue<T>(m_pField->offset);
        }

        template<typename T>
        __inline void SetMemberValue(Unity::il2cppFieldInfo* m_pField, T m_tValue)
        {
            if (!m_pField || 0 > m_pField->offset)
                return;

            SetMemberValue<T>(m_pField->offset, m_tValue);
        }

        template<typename T>
        T GetMemberValue(const char* m_pMemberName)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMemberName);
            if (pField)
            {
                if (pField->offset >= 0) return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->offset);
            }
            else
                return GetPropertyValue<T>(m_pMemberName);

            T tDefault = {};
            return tDefault;
        }

        template<typename T>
        void SetMemberValue(const char* m_pMemberName, T m_tValue)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMemberName);
            if (pField)
            {
                if (pField->offset >= 0) *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->offset) = m_tValue;
                return;
            }

            SetPropertyValue<T>(m_pMemberName, m_tValue);
        }

        template<typename T>
        __inline T GetObscuredViaOffset(int m_iOffset)
        {
            if (m_iOffset >= 0)
            {
                switch (sizeof(T))
                {
                    case sizeof(double) :
                    {
                        long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        long long m_lValue = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

                        m_lValue ^= m_lKey;
                        return *reinterpret_cast<T*>(&m_lValue);
                    }
                    break;
                    case sizeof(int) :
                    {
                        int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        int m_iValue = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

                        m_iValue ^= m_iKey;
                        return *reinterpret_cast<T*>(&m_iValue);
                    }
                    break;
                    case sizeof(bool) :
                    {
                        unsigned char m_uKey = *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        int m_iValue = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_uKey));

                        m_iValue ^= m_uKey;
                        return *reinterpret_cast<T*>(&m_iValue);
                    }
                    break;
                }
            }

            T m_tDefault = { 0 };
            return m_tDefault;
        }

        template<typename T>
        T GetObscuredValue(const char* m_pMemberName)
        {
            Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMemberName);
            return GetObscuredViaOffset<T>(m_pField ? m_pField->offset : -1);
        }

        template<typename T>
        __inline void SetObscuredViaOffset(int m_iOffset, T m_tValue)
        {
            if (0 > m_iOffset)
                return;

            switch (sizeof(T))
            {
                case sizeof(double) :
                {
                    long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    long long* m_pValue = reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

                    *m_pValue = *reinterpret_cast<long long*>(&m_tValue) ^ m_lKey;
                }
                break;
                case sizeof(int) :
                {
                    int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    int* m_pValue = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

                    *m_pValue = *reinterpret_cast<int*>(&m_tValue) ^ m_iKey;
                }
                break;
                case sizeof(bool) :
                {
                    unsigned char m_uKey = *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    int* m_pValue = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_uKey));

                    *m_pValue = *reinterpret_cast<int*>(&m_tValue) ^ m_uKey;
                }
                break;
            }
        }

        template<typename T>
        void SetObscuredValue(const char* m_pMemberName, T m_tValue)
        {
            Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMemberName);
            if (!m_pField)
                return;

            SetObscuredViaOffset<T>(m_pField->offset, m_tValue);
        }

        bool IsGeneric()
        {
            return Class::IsGeneric(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        bool IsInflated()
        {
            return Class::IsInflated(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        bool IsValueType()
        {
            return Class::IsValueType(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        bool IsEnum()
        {
            return Class::IsEnum(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        bool IsAssignableFrom(Unity::il2cppClass* m_pFrom)
        {
            return Class::IsAssignableFrom(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pFrom);
        }

        bool IsSubclassOf(Unity::il2cppClass* m_pKlass, bool m_bCheckInterfaces = false)
        {
            return Class::IsSubclassOf(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pKlass, m_bCheckInterfaces);
        }

        Unity::il2cppClass* GetParentClass()
        {
            return Class::GetParent(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        Unity::il2cppClass* GetDeclaringType()
        {
            return Class::GetDeclaringType(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass));
        }

        void* Unbox()
        {
            return Class::ObjectUnbox(reinterpret_cast<Unity::il2cppObject*>(this));
        }

        template<typename T>
        T* UnboxAs()
        {
            return reinterpret_cast<T*>(Class::ObjectUnbox(reinterpret_cast<Unity::il2cppObject*>(this)));
        }

        template<typename T>
        Unity::il2cppObject* Box(T* m_pData)
        {
            return Class::ValueBox(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), reinterpret_cast<void*>(m_pData));
        }

        template<typename Ret, typename... Args>
        typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
        CallMethod(const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) { Ret m_tDefault{}; return m_tDefault; }
            return reinterpret_cast<Ret(UNITY_CALLING_CONVENTION)(void*, Args...)>(m_pPtr)(this, args...);
        }

        template<typename Ret = void, typename... Args>
        typename std::enable_if<std::is_void<Ret>::value>::type
        CallMethod(const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(reinterpret_cast<Unity::il2cppClass*>(m_Object.klass), m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Args...)>(m_pPtr)(this, args...);
        }

        template<typename Ret, typename... Args>
        static typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
        CallMethod(Unity::il2cppClass* m_pClass, const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(m_pClass, m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) { Ret m_tDefault{}; return m_tDefault; }
            return reinterpret_cast<Ret(UNITY_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
        }

        template<typename Ret = void, typename... Args>
        static typename std::enable_if<std::is_void<Ret>::value>::type
        CallMethod(Unity::il2cppClass* m_pClass, const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(m_pClass, m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
        }

        template<typename Ret, typename... Args>
        static typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
        CallMethod(const char* m_pClassName, const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(m_pClassName, m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) { Ret m_tDefault{}; return m_tDefault; }
            return reinterpret_cast<Ret(UNITY_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
        }

        template<typename Ret = void, typename... Args>
        static typename std::enable_if<std::is_void<Ret>::value>::type
        CallMethod(const char* m_pClassName, const char* m_pMethodName, Args... args)
        {
            void* m_pPtr = Class::Utils::GetMethodPointer(m_pClassName, m_pMethodName, static_cast<int>(sizeof...(Args)));
            if (!m_pPtr) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(Args...)>(m_pPtr)(args...);
        }

        bool IsInstanceOf(Unity::il2cppClass* m_pClass)
        {
            return Class::Utils::IsInstanceOf(reinterpret_cast<Unity::il2cppObject*>(this), m_pClass);
        }
    };
}