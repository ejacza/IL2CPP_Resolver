#pragma once

namespace Unity
{
    struct LayerMaskFunctions_t
    {
        void* m_LayerToName = nullptr;
        void* m_NameToLayer = nullptr;
    };
    LayerMaskFunctions_t m_LayerMaskFunctions;

    namespace LayerMask
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_LAYERMASK_CLASS);

            m_LayerMaskFunctions.m_LayerToName = IL2CPP::ResolveCall(UNITY_LAYERMASK_LAYERTONAME);
            m_LayerMaskFunctions.m_NameToLayer = IL2CPP::ResolveCall(UNITY_LAYERMASK_NAMETOLAYER);
        }

        System_String* LayerToName(unsigned int m_uLayer)
        {
            if (!m_LayerMaskFunctions.m_LayerToName) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(unsigned int, void*)>(m_LayerMaskFunctions.m_LayerToName)(m_uLayer, nullptr);
        }

        uint32_t NameToLayer(const char* m_pName)
        {
            if (!m_LayerMaskFunctions.m_NameToLayer) return 0U;
            return reinterpret_cast<uint32_t(UNITY_CALLING_CONVENTION)(void*, void*)>(m_LayerMaskFunctions.m_NameToLayer)(IL2CPP::String::New(m_pName), nullptr);
        }
    }
}