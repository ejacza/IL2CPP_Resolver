#pragma once

namespace IL2CPP
{
    void* ResolveCall(const char* m_Name)
    {
        void* result = reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(const char*)>(Functions.m_ResolveFunction)(m_Name);
        LOGI("[ResolveCall] %s -> %p", m_Name, result);
        return result;
    }
}