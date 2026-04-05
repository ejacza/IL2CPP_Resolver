#pragma once

namespace Unity
{
    struct ShaderFunctions_t
    {
        void* m_Find = nullptr;
        void* m_PropertyToID = nullptr;
        void* m_EnableKeyword = nullptr;
        void* m_DisableKeyword = nullptr;
        void* m_SetGlobalFloat = nullptr;
    };
    ShaderFunctions_t m_ShaderFunctions;

    class CShader : public CObject
    {
    };

    namespace Shader
    {
        CShader* Find(const char* name)
        {
            if (!m_ShaderFunctions.m_Find) return nullptr;
            return reinterpret_cast<CShader*(UNITY_CALLING_CONVENTION)(System_String*)>(m_ShaderFunctions.m_Find)(IL2CPP::String::New(name));
        }

        int PropertyToID(const char* name)
        {
            if (!m_ShaderFunctions.m_PropertyToID) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(System_String*)>(m_ShaderFunctions.m_PropertyToID)(IL2CPP::String::New(name));
        }

        void EnableKeyword(const char* keyword)
        {
            if (!m_ShaderFunctions.m_EnableKeyword) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(System_String*)>(m_ShaderFunctions.m_EnableKeyword)(IL2CPP::String::New(keyword));
        }

        void DisableKeyword(const char* keyword)
        {
            if (!m_ShaderFunctions.m_DisableKeyword) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(System_String*)>(m_ShaderFunctions.m_DisableKeyword)(IL2CPP::String::New(keyword));
        }

        void SetGlobalFloat(int nameID, float value)
        {
            if (!m_ShaderFunctions.m_SetGlobalFloat) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(int, float)>(m_ShaderFunctions.m_SetGlobalFloat)(nameID, value);
        }

        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_SHADER_CLASS);

            m_ShaderFunctions.m_Find           = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SHADER_CLASS, "Find", 1);
            m_ShaderFunctions.m_PropertyToID   = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SHADER_CLASS, "PropertyToID", 1);
            m_ShaderFunctions.m_EnableKeyword  = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SHADER_CLASS, "EnableKeyword", 1);
            m_ShaderFunctions.m_DisableKeyword = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SHADER_CLASS, "DisableKeyword", 1);
            m_ShaderFunctions.m_SetGlobalFloat = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SHADER_CLASS, "SetGlobalFloat", 2);
        }
    }
}
