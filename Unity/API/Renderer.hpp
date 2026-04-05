#pragma once

namespace Unity
{
    struct RendererFunctions_t
    {
        void* m_GetMaterials = nullptr;
        void* m_SetMaterials = nullptr;
        void* m_GetMaterial = nullptr;
        void* m_SetMaterial = nullptr;
        void* m_GetSharedMaterials = nullptr;
        void* m_SetSharedMaterials = nullptr;
        void* m_GetEnabled = nullptr;
        void* m_SetEnabled = nullptr;
    };
    RendererFunctions_t m_RendererFunctions;

    class CRenderer : public CComponent
    {
    public:
        il2cppArray<CMaterial*>* GetMaterials()
        {
            if (!m_RendererFunctions.m_GetMaterials) return nullptr;
            return reinterpret_cast<il2cppArray<CMaterial*>*(UNITY_CALLING_CONVENTION)(void*)>(m_RendererFunctions.m_GetMaterials)(this);
        }

        void SetMaterials(il2cppArray<CMaterial*>* value)
        {
            if (!m_RendererFunctions.m_SetMaterials) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*)>(m_RendererFunctions.m_SetMaterials)(this, value);
        }

        CMaterial* GetMaterial()
        {
            if (!m_RendererFunctions.m_GetMaterial) return nullptr;
            return reinterpret_cast<CMaterial*(UNITY_CALLING_CONVENTION)(void*)>(m_RendererFunctions.m_GetMaterial)(this);
        }

        void SetMaterial(CMaterial* value)
        {
            if (!m_RendererFunctions.m_SetMaterial) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*)>(m_RendererFunctions.m_SetMaterial)(this, value);
        }

        il2cppArray<CMaterial*>* GetSharedMaterials()
        {
            if (!m_RendererFunctions.m_GetSharedMaterials) return nullptr;
            return reinterpret_cast<il2cppArray<CMaterial*>*(UNITY_CALLING_CONVENTION)(void*)>(m_RendererFunctions.m_GetSharedMaterials)(this);
        }

        void SetSharedMaterials(il2cppArray<CMaterial*>* value)
        {
            if (!m_RendererFunctions.m_SetSharedMaterials) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*)>(m_RendererFunctions.m_SetSharedMaterials)(this, value);
        }

        bool GetEnabled()
        {
            if (!m_RendererFunctions.m_GetEnabled) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(m_RendererFunctions.m_GetEnabled)(this);
        }

        void SetEnabled(bool value)
        {
            if (!m_RendererFunctions.m_SetEnabled) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(m_RendererFunctions.m_SetEnabled)(this, value);
        }
    };

    namespace Renderer
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_RENDERER_CLASS);

            m_RendererFunctions.m_GetMaterials       = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "get_materials");
            m_RendererFunctions.m_SetMaterials       = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "set_materials", 1);
            m_RendererFunctions.m_GetMaterial        = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "get_material");
            m_RendererFunctions.m_SetMaterial        = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "set_material", 1);
            m_RendererFunctions.m_GetSharedMaterials = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "get_sharedMaterials");
            m_RendererFunctions.m_SetSharedMaterials = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "set_sharedMaterials", 1);
            m_RendererFunctions.m_GetEnabled         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "get_enabled");
            m_RendererFunctions.m_SetEnabled         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_RENDERER_CLASS, "set_enabled", 1);
        }
    }
}
