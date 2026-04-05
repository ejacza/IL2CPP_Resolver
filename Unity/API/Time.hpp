#pragma once

namespace Unity
{
    struct TimeFunctions_t
    {
        void* m_GetFixedDeltaTime = nullptr;
        void* m_GetTimeScale = nullptr;
        void* m_SetTimeScale = nullptr;
        void* m_GetDeltaTime = nullptr;
        void* m_GetTime = nullptr;
    };
    TimeFunctions_t m_TimeFunctions;

    namespace Time
    {
        void Initialize()
        {
            m_TimeFunctions.m_GetFixedDeltaTime = IL2CPP::ResolveCall(UNITY_TIME_GETFIXEDDELTAIME);
            m_TimeFunctions.m_GetTimeScale      = IL2CPP::ResolveCall(UNITY_TIME_GETTIMESCALE);
            m_TimeFunctions.m_SetTimeScale      = IL2CPP::ResolveCall(UNITY_TIME_SETTIMESCALE);
            m_TimeFunctions.m_GetDeltaTime      = IL2CPP::ResolveCall(UNITY_TIME_GETDELTAIME);
            m_TimeFunctions.m_GetTime           = IL2CPP::ResolveCall(UNITY_TIME_GETTIME);
        }

        float FixedDeltaTime()
        {
            if (!m_TimeFunctions.m_GetFixedDeltaTime) return 0.0f;
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_TimeFunctions.m_GetFixedDeltaTime)(nullptr);
        }

        float TimeScale()
        {
            if (!m_TimeFunctions.m_GetTimeScale) return 0.0f;
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_TimeFunctions.m_GetTimeScale)(nullptr);
        }

        void SetTimeScale(float m_fValue)
        {
            if (!m_TimeFunctions.m_SetTimeScale) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(float, void*)>(m_TimeFunctions.m_SetTimeScale)(m_fValue, nullptr);
        }

        float DeltaTime()
        {
            if (!m_TimeFunctions.m_GetDeltaTime) return 0.0f;
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_TimeFunctions.m_GetDeltaTime)(nullptr);
        }

        float GetTime()
        {
            if (!m_TimeFunctions.m_GetTime) return 0.0f;
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_TimeFunctions.m_GetTime)(nullptr);
        }
    }
}