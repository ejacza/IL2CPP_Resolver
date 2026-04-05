#pragma once

namespace Unity
{
    struct ScreenFunctions_t
    {
        void* m_GetWidth = nullptr;
        void* m_GetHeight = nullptr;
        void* m_GetDpi = nullptr;
        void* m_SetResolution = nullptr;
    };
    ScreenFunctions_t m_ScreenFunctions;

    namespace Screen
    {
        void Initialize()
        {
            m_ScreenFunctions.m_GetWidth      = IL2CPP::ResolveCall(UNITY_SCREEN_GETWIDTH);
            m_ScreenFunctions.m_GetHeight     = IL2CPP::ResolveCall(UNITY_SCREEN_GETHEIGHT);
            m_ScreenFunctions.m_GetDpi        = IL2CPP::ResolveCall(UNITY_SCREEN_GETDPI);
            m_ScreenFunctions.m_SetResolution = IL2CPP::Class::Utils::GetMethodPointer(UNITY_SCREEN_CLASS, "SetResolution", {"Int32", "Int32", "Boolean"});
        }

        int getWidth()
        {
            if (!m_ScreenFunctions.m_GetWidth) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(void*)>(m_ScreenFunctions.m_GetWidth)(nullptr);
        }

        int getHeight()
        {
            if (!m_ScreenFunctions.m_GetHeight) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(void*)>(m_ScreenFunctions.m_GetHeight)(nullptr);
        }

        float getDpi()
        {
            if (!m_ScreenFunctions.m_GetDpi) return 0.0f;
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_ScreenFunctions.m_GetDpi)(nullptr);
        }

        void setResolution(int m_iWidth, int m_iHeight, bool m_bFullscreen)
        {
            if (!m_ScreenFunctions.m_SetResolution) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(int, int, bool)>(m_ScreenFunctions.m_SetResolution)(m_iWidth, m_iHeight, m_bFullscreen);
        }
    }
}
