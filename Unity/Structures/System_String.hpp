#pragma once

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
#pragma clang diagnostic ignored "-Wtautological-pointer-compare"
#endif

namespace Unity
{
    struct System_String : il2cppObject
    {
        int32_t m_iLength;
        wchar_t m_wString[1024];

        void Clear()
        {
            if (this == nullptr) return;
            memset(m_wString, 0, static_cast<size_t>(m_iLength) * 2);
            m_iLength = 0;
        }

        wchar_t* ToWideString()
        {
            return m_wString;
        }

        int32_t ToLength()
        {
            return m_iLength;
        }

        std::string ToString()
        {
            if (this == nullptr) return "";
            int32_t len = reinterpret_cast<int32_t(IL2CPP_CALLING_CONVENTION)(void*)>(IL2CPP::Functions.m_StringLength)(this);
            if (len <= 0) return "";
            uint16_t* chars = reinterpret_cast<uint16_t*(IL2CPP_CALLING_CONVENTION)(void*)>(IL2CPP::Functions.m_StringChars)(this);
            if (!chars) return "";
            std::string result;
            result.reserve(static_cast<size_t>(len));
            mbstate_t state{};
            char buf[MB_LEN_MAX];
            for (int32_t i = 0; i < len; i++) {
                size_t n = wcrtomb(buf, static_cast<wchar_t>(chars[i]), &state);
                if (n != (size_t)-1)
                    result.append(buf, n);
            }
            return result;
        }
    };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif