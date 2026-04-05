#pragma once

namespace Unity
{
    struct MaterialFunctions_t
    {
        void* m_Ctor = nullptr;
        void* m_GetShader = nullptr;
        void* m_SetShader = nullptr;
        void* m_GetColor = nullptr;
        void* m_SetColor = nullptr;
        void* m_SetColorByID = nullptr;
        void* m_SetRenderQueue = nullptr;
        void* m_EnableKeyword = nullptr;
        void* m_DisableKeyword = nullptr;
        void* m_SetFloat = nullptr;
        void* m_SetFloatByID = nullptr;
        void* m_CopyPropertiesFromMaterial = nullptr;
    };
    MaterialFunctions_t m_MaterialFunctions;

    class CMaterial : public CObject
    {
    public:
        void Init(CShader* shader)
        {
            if (!m_MaterialFunctions.m_Ctor) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, CShader*)>(m_MaterialFunctions.m_Ctor)(this, shader);
        }

        CShader* GetShader()
        {
            if (!m_MaterialFunctions.m_GetShader) return nullptr;
            return reinterpret_cast<CShader*(UNITY_CALLING_CONVENTION)(void*)>(m_MaterialFunctions.m_GetShader)(this);
        }

        void SetShader(CShader* value)
        {
            if (!m_MaterialFunctions.m_SetShader) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, CShader*)>(m_MaterialFunctions.m_SetShader)(this, value);
        }

        Color GetColor()
        {
            if (!m_MaterialFunctions.m_GetColor) return Color();
            return reinterpret_cast<Color(UNITY_CALLING_CONVENTION)(void*)>(m_MaterialFunctions.m_GetColor)(this);
        }

        void SetColor(Color value)
        {
            if (!m_MaterialFunctions.m_SetColor) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Color)>(m_MaterialFunctions.m_SetColor)(this, value);
        }

        void SetColor(int nameID, Color value)
        {
            if (!m_MaterialFunctions.m_SetColorByID) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, int, Color)>(m_MaterialFunctions.m_SetColorByID)(this, nameID, value);
        }

        void SetColor(const char* name, Color value)
        {
            SetColor(Unity::Shader::PropertyToID(name), value);
        }

        void SetRenderQueue(int value)
        {
            if (!m_MaterialFunctions.m_SetRenderQueue) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, int)>(m_MaterialFunctions.m_SetRenderQueue)(this, value);
        }

        void EnableKeyword(const char* keyword)
        {
            if (!m_MaterialFunctions.m_EnableKeyword) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, System_String*)>(m_MaterialFunctions.m_EnableKeyword)(this, IL2CPP::String::New(keyword));
        }

        void DisableKeyword(const char* keyword)
        {
            if (!m_MaterialFunctions.m_DisableKeyword) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, System_String*)>(m_MaterialFunctions.m_DisableKeyword)(this, IL2CPP::String::New(keyword));
        }

        void SetFloat(const char* name, float value)
        {
            if (!m_MaterialFunctions.m_SetFloat) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, System_String*, float)>(m_MaterialFunctions.m_SetFloat)(this, IL2CPP::String::New(name), value);
        }

        void SetFloat(int nameID, float value)
        {
            if (!m_MaterialFunctions.m_SetFloatByID) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, int, float)>(m_MaterialFunctions.m_SetFloatByID)(this, nameID, value);
        }

        void CopyPropertiesFromMaterial(CMaterial* mat)
        {
            if (!m_MaterialFunctions.m_CopyPropertiesFromMaterial) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*)>(m_MaterialFunctions.m_CopyPropertiesFromMaterial)(this, mat);
        }
    };

    namespace Material
    {
        CMaterial* Create(CShader* shader)
        {
            Unity::il2cppClass* klass = IL2CPP::Class::Find(UNITY_MATERIAL_CLASS);
            if (!klass || !IL2CPP::Functions.m_pObjectNew) return nullptr;
            CMaterial* mat = reinterpret_cast<CMaterial*(IL2CPP_CALLING_CONVENTION)(void*)>(IL2CPP::Functions.m_pObjectNew)(klass);
            if (mat)
                mat->Init(shader);
            return mat;
        }

        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_MATERIAL_CLASS);

            m_MaterialFunctions.m_Ctor                   = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, ".ctor", 1);
            m_MaterialFunctions.m_GetShader              = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "get_shader");
            m_MaterialFunctions.m_SetShader              = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "set_shader", 1);
            m_MaterialFunctions.m_GetColor               = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "get_color");
            m_MaterialFunctions.m_SetColor               = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "set_color", 1);
            m_MaterialFunctions.m_SetColorByID           = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "SetColor", 2);
            m_MaterialFunctions.m_SetRenderQueue         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "set_renderQueue", 1);
            m_MaterialFunctions.m_EnableKeyword          = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "EnableKeyword", 1);
            m_MaterialFunctions.m_DisableKeyword         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "DisableKeyword", 1);
            m_MaterialFunctions.m_SetFloat               = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "SetFloat", 2);
            m_MaterialFunctions.m_SetFloatByID           = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "SetFloat", 2);
            m_MaterialFunctions.m_CopyPropertiesFromMaterial = IL2CPP::Class::Utils::GetMethodPointer(UNITY_MATERIAL_CLASS, "CopyPropertiesFromMaterial", 1);
        }
    }
}
