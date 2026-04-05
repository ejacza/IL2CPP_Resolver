#pragma once

namespace Unity
{
    struct RigidbodyFunctions_t
    {
        void* m_GetDetectCollisions = nullptr;
        void* m_GetVelocity = nullptr;
        void* m_SetDetectCollisions = nullptr;
        void* m_SetVelocity = nullptr;
    };
    RigidbodyFunctions_t m_RigidbodyFunctions;

    class CRigidbody : public IL2CPP::CClass
    {
    public:
        bool GetDetectCollisions()
        {
            if (!m_RigidbodyFunctions.m_GetDetectCollisions) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(m_RigidbodyFunctions.m_GetDetectCollisions)(this);
        }

        void SetDetectCollisions(bool m_bDetect)
        {
            if (!m_RigidbodyFunctions.m_SetDetectCollisions) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(m_RigidbodyFunctions.m_SetDetectCollisions)(this, m_bDetect);
        }

        Vector3 GetVelocity()
        {
            Vector3 vRet;
            if (!m_RigidbodyFunctions.m_GetVelocity) return vRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(m_RigidbodyFunctions.m_GetVelocity)(this, vRet);
            return vRet;
        }

        void SetVelocity(Vector3 m_vVector)
        {
            if (!m_RigidbodyFunctions.m_SetVelocity) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(m_RigidbodyFunctions.m_SetVelocity)(this, m_vVector);
        }
    };

    namespace RigidBody
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_RIGIDBODY_CLASS);

            m_RigidbodyFunctions.m_GetDetectCollisions = IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETDETECTCOLLISIONS);
            m_RigidbodyFunctions.m_GetVelocity         = IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETVELOCITY);
            m_RigidbodyFunctions.m_SetDetectCollisions = IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETDETECTCOLLISIONS);
            m_RigidbodyFunctions.m_SetVelocity         = IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETVELOCITY);
        }
    }
}