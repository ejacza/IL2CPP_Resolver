#pragma once

namespace IL2CPP
{
    namespace Thread
    {
        void* Attach(void* m_Domain)
        {
            return reinterpret_cast<void* (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ThreadAttach)(m_Domain);
        }

        void Detach(void* m_Thread)
        {
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ThreadDetach)(m_Thread);
        }
    }

    class CThread
    {
    public:
        void* m_OnStart   = nullptr;
        void* m_UserData  = nullptr;

        static void Handler(void* m_Reserved)
        {
            void* m_IL2CPPThread = Thread::Attach(Domain::Get());

            CThread* m_Thread     = reinterpret_cast<CThread*>(m_Reserved);
            void*    m_ThreadStart = m_Thread->m_OnStart;
            void*    m_ThreadData  = m_Thread->m_UserData;
            delete m_Thread;

            reinterpret_cast<void(*)(void*)>(m_ThreadStart)(m_ThreadData);

            Thread::Detach(m_IL2CPPThread);
        }

        CThread() {}
        CThread(void* m_OnStartFunc, void* m_UserDataPtr)
        {
            m_OnStart  = m_OnStartFunc;
            m_UserData = m_UserDataPtr;

            if (!m_OnStart)
            {
                IL2CPP_ASSERT("IL2CPP::CThread - m_OnStart is nullptr");
                return;
            }

            std::thread(Handler, this).detach();
        }
    };

    namespace Thread
    {
        void Create(void* m_OnStartFunc, void* m_UserData = nullptr)
        {
            CThread* m_Thread = new CThread(m_OnStartFunc, m_UserData);
            IL2CPP_ASSERT(m_Thread && "IL2CPP::Thread::Create - Failed!");
        }
    }
}
