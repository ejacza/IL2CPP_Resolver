#pragma once

namespace Unity
{
	namespace Obfuscators
	{
        void ROT_String_InPlace(char* pBuffer, int iValue)
        {
            for (size_t i = 0; pBuffer[i] != '\0'; ++i)
            {
                bool bIsUppercase = pBuffer[i] >= 'A' && 'Z' >= pBuffer[i];
                bool bIsLowercase = !bIsUppercase && pBuffer[i] >= 'a' && 'z' >= pBuffer[i];
                if (!bIsUppercase && !bIsLowercase) continue;

                int iNewValue = static_cast<int>(pBuffer[i]) + iValue;
                if (bIsUppercase)
                {
                    int iMaxValue = static_cast<int>('Z');
                    while (iNewValue > iMaxValue) iNewValue = static_cast<int>('A') + (iNewValue - iMaxValue);
                }
                else
                {
                    int iMaxValue = static_cast<int>('z');
                    while (iNewValue > iMaxValue) iNewValue = static_cast<int>('a') + (iNewValue - iMaxValue);
                }

                pBuffer[i] = static_cast<char>(iNewValue);
            }
        }

        void XOR_String_InPlace(char* pBuffer, int iKey)
        {
            for (size_t i = 0; pBuffer[i] != '\0'; ++i)
                pBuffer[i] ^= static_cast<char>(iKey);
        }

        std::string ROT_String(const char* pString, int iValue)
        {
            std::string sRet(pString);
            ROT_String_InPlace(&sRet[0], iValue);
            return sRet;
        }

        std::string XOR_String(const char* pString, int iKey)
        {
            std::string sRet(pString);
            XOR_String_InPlace(&sRet[0], iKey);
            return sRet;
        }
	}
}
