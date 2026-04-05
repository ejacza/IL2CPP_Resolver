#pragma once

namespace Unity
{
    struct ApplicationFunctions_t
    {
        void* m_OpenURL = nullptr;
        void* m_Quit = nullptr;
        void* m_GetPersistentDataPath = nullptr;
        void* m_GetUnityVersion = nullptr;
        void* m_GetVersion = nullptr;
        void* m_GetProductName = nullptr;
    };
    ApplicationFunctions_t m_ApplicationFunctions;

    namespace Application
    {
        void Initialize()
        {
            m_ApplicationFunctions.m_OpenURL               = IL2CPP::ResolveCall(UNITY_APPLICATION_OPENURL);
            m_ApplicationFunctions.m_Quit                  = IL2CPP::ResolveCall(UNITY_APPLICATION_QUIT);
            m_ApplicationFunctions.m_GetPersistentDataPath = IL2CPP::ResolveCall(UNITY_APPLICATION_GETPERSISTENTDATAPATH);
            m_ApplicationFunctions.m_GetUnityVersion       = IL2CPP::ResolveCall(UNITY_APPLICATION_GETUNITYVERSION);
            m_ApplicationFunctions.m_GetVersion            = IL2CPP::ResolveCall(UNITY_APPLICATION_GETVERSION);
            m_ApplicationFunctions.m_GetProductName        = IL2CPP::ResolveCall(UNITY_APPLICATION_GETPRODUCTNAME);
        }

        void OpenURL(const char* m_URL)
        {
            if (!m_ApplicationFunctions.m_OpenURL) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(System_String*, void*)>(m_ApplicationFunctions.m_OpenURL)(IL2CPP::String::New(m_URL), nullptr);
        }

        void Quit(int m_iExitCode = 0)
        {
            if (!m_ApplicationFunctions.m_Quit) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(int, void*)>(m_ApplicationFunctions.m_Quit)(m_iExitCode, nullptr);
        }

        System_String* PersistentDataPath()
        {
            if (!m_ApplicationFunctions.m_GetPersistentDataPath) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ApplicationFunctions.m_GetPersistentDataPath)(nullptr);
        }

        System_String* UnityVersion()
        {
            if (!m_ApplicationFunctions.m_GetUnityVersion) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ApplicationFunctions.m_GetUnityVersion)(nullptr);
        }

        System_String* Version()
        {
            if (!m_ApplicationFunctions.m_GetVersion) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ApplicationFunctions.m_GetVersion)(nullptr);
        }

        System_String* ProductName()
        {
            if (!m_ApplicationFunctions.m_GetProductName) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ApplicationFunctions.m_GetProductName)(nullptr);
        }
    }
}