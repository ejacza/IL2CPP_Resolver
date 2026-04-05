#pragma once

namespace IL2CPP
{
    namespace Utils
    {
        namespace VTable
        {
            void ReplaceFunction(void** m_VTableFunc, void* m_NewFunc, void** m_Original = nullptr)
            {
                if (!m_VTableFunc || !m_NewFunc)
                    return;

                long pageSize = sysconf(_SC_PAGESIZE);
                if (pageSize <= 0)
                    return;

                uintptr_t pageStart = reinterpret_cast<uintptr_t>(m_VTableFunc) & ~static_cast<uintptr_t>(pageSize - 1);

                if (mprotect(reinterpret_cast<void*>(pageStart), static_cast<size_t>(pageSize), PROT_READ | PROT_WRITE) != 0)
                    return;

                if (m_Original)
                    *m_Original = *m_VTableFunc;

                *m_VTableFunc = m_NewFunc;

                __builtin___clear_cache(
                    reinterpret_cast<char*>(m_VTableFunc),
                    reinterpret_cast<char*>(m_VTableFunc) + sizeof(void*)
                );

                mprotect(reinterpret_cast<void*>(pageStart), static_cast<size_t>(pageSize), PROT_READ | PROT_EXEC);
            }

            void** FindFunction(void** m_VTable, int m_Count, std::initializer_list<unsigned char> m_Opcodes)
            {
                if (!m_VTable || m_Count <= 0 || m_Opcodes.size() == 0)
                    return nullptr;

                const size_t m_OpcodeSize         = m_Opcodes.size();
                const unsigned char* m_OpcodesPtr = m_Opcodes.begin();

                for (int i = 0; i < m_Count; ++i)
                {
                    uintptr_t m_uEntry = reinterpret_cast<uintptr_t>(m_VTable[i]);
                    if (m_uEntry < 0x1000ULL)
                        continue;

                    const unsigned char* m_FuncBytes = reinterpret_cast<const unsigned char*>(m_uEntry);

                    bool m_Match = true;
                    for (size_t j = 0; j < m_OpcodeSize; ++j)
                    {
                        if (m_OpcodesPtr[j] == 0xFF)
                            continue;
                        if (m_FuncBytes[j] != m_OpcodesPtr[j])
                        {
                            m_Match = false;
                            break;
                        }
                    }

                    if (m_Match)
                        return &m_VTable[i];
                }

                return nullptr;
            }
        }
    }
}