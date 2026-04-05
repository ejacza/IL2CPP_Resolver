#pragma once

namespace Unity
{
    struct RaycastHit
    {
        Vector3 m_Point;
        Vector3 m_Normal;
        Vector3 m_BarycentricCoordinate;
        float   m_Distance            = 0.f;
        int     m_ColliderInstanceID  = 0;
        float   m_UV[2]               = { 0.f, 0.f };
        float   m_UV2[2]              = { 0.f, 0.f };
    };
    
    enum m_eQueryTriggerInteraction : int
    {
        m_eQueryTriggerInteraction_UseGlobal = 0,
        m_eQueryTriggerInteraction_Collide   = 1,
        m_eQueryTriggerInteraction_Ignore    = 2,
    };

    class CCollider : public CComponent {};

    struct PhysicsFunctions_t
    {
        void* m_GetGravity            = nullptr;
        void* m_IgnoreCollision       = nullptr;
        void* m_Raycast               = nullptr;
        void* m_RaycastSimple         = nullptr;
        void* m_RaycastAll            = nullptr;
        void* m_RaycastNonAlloc       = nullptr;
        void* m_SphereCast            = nullptr;
        void* m_SphereCastNonAlloc    = nullptr;
        void* m_OverlapSphere         = nullptr;
        void* m_OverlapSphereNonAlloc = nullptr;
        void* m_ComputePenetration    = nullptr;
    };
    PhysicsFunctions_t m_PhysicsFunctions;

    namespace Physics
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_PHYSICS_CLASS);

            m_PhysicsFunctions.m_GetGravity            = IL2CPP::ResolveCall(UNITY_PHYSICS_GETGRAVITY);
            m_PhysicsFunctions.m_IgnoreCollision       = IL2CPP::ResolveCall(UNITY_PHYSICS_IGNORECOLLISION);
            m_PhysicsFunctions.m_Raycast               = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "Raycast", 6);
            m_PhysicsFunctions.m_RaycastSimple         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "Raycast",         {"Vector3", "Vector3", "Single", "Int32"});
            m_PhysicsFunctions.m_RaycastAll            = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "RaycastAll",      {"Vector3", "Vector3", "Single", "Int32"});
            m_PhysicsFunctions.m_RaycastNonAlloc       = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "RaycastNonAlloc", {"Vector3", "Vector3"});
            m_PhysicsFunctions.m_SphereCast            = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "SphereCast",      7);
            m_PhysicsFunctions.m_SphereCastNonAlloc    = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "SphereCastNonAlloc", 6);
            m_PhysicsFunctions.m_OverlapSphere         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "OverlapSphere",         3);
            m_PhysicsFunctions.m_OverlapSphereNonAlloc = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "OverlapSphereNonAlloc", 4);
            m_PhysicsFunctions.m_ComputePenetration    = IL2CPP::Class::Utils::GetMethodPointer(UNITY_PHYSICS_CLASS, "ComputePenetration", 8);
        }

        Vector3 GetGravity()
        {
            Vector3 m_vRet;
            if (!m_PhysicsFunctions.m_GetGravity) return m_vRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(Vector3*)>(m_PhysicsFunctions.m_GetGravity)(&m_vRet);
            return m_vRet;
        }

        void IgnoreCollision(CCollider* m_pColliderA, CCollider* m_pColliderB, bool m_bIgnore = true)
        {
            if (!m_PhysicsFunctions.m_IgnoreCollision) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*, bool)>(m_PhysicsFunctions.m_IgnoreCollision)(m_pColliderA, m_pColliderB, m_bIgnore);
        }

        bool Raycast(Vector3 m_vOrigin, Vector3 m_vDirection, RaycastHit& m_Hit, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1, m_eQueryTriggerInteraction m_eQTI = m_eQueryTriggerInteraction_UseGlobal)
        {
            if (!m_PhysicsFunctions.m_Raycast) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(Vector3, Vector3, RaycastHit*, float, int, int)>(m_PhysicsFunctions.m_Raycast)(m_vOrigin, m_vDirection, &m_Hit, m_fMaxDistance, m_iLayerMask, static_cast<int>(m_eQTI));
        }

        bool Raycast(Vector3 m_vOrigin, Vector3 m_vDirection, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_RaycastSimple) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(Vector3, Vector3, float, int)>(m_PhysicsFunctions.m_RaycastSimple)(m_vOrigin, m_vDirection, m_fMaxDistance, m_iLayerMask);
        }

        bool RaycastFromRay(Ray m_Ray, RaycastHit& m_Hit, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1, m_eQueryTriggerInteraction m_eQTI = m_eQueryTriggerInteraction_UseGlobal)
        {
            return Raycast(m_Ray.m_vOrigin, m_Ray.m_vDirection, m_Hit, m_fMaxDistance, m_iLayerMask, m_eQTI);
        }

        il2cppArray<RaycastHit>* RaycastAll(Vector3 m_vOrigin, Vector3 m_vDirection, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_RaycastAll) return nullptr;
            return reinterpret_cast<il2cppArray<RaycastHit>*(UNITY_CALLING_CONVENTION)(Vector3, Vector3, float, int)>(m_PhysicsFunctions.m_RaycastAll)(m_vOrigin, m_vDirection, m_fMaxDistance, m_iLayerMask);
        }

        il2cppArray<RaycastHit>* RaycastAll(Ray m_Ray, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            return RaycastAll(m_Ray.m_vOrigin, m_Ray.m_vDirection, m_fMaxDistance, m_iLayerMask);
        }

        int RaycastNonAlloc(Vector3 m_vOrigin, Vector3 m_vDirection, il2cppArray<RaycastHit>* m_pResults, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_RaycastNonAlloc || !m_pResults) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(Vector3, Vector3, void*, float, int)>(m_PhysicsFunctions.m_RaycastNonAlloc)(m_vOrigin, m_vDirection, m_pResults, m_fMaxDistance, m_iLayerMask);
        }

        int RaycastNonAlloc(Ray m_Ray, il2cppArray<RaycastHit>* m_pResults, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            return RaycastNonAlloc(m_Ray.m_vOrigin, m_Ray.m_vDirection, m_pResults, m_fMaxDistance, m_iLayerMask);
        }

        bool SphereCast(Vector3 m_vOrigin, float m_fRadius, Vector3 m_vDirection, RaycastHit& m_Hit, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1, m_eQueryTriggerInteraction m_eQTI = m_eQueryTriggerInteraction_UseGlobal)
        {
            if (!m_PhysicsFunctions.m_SphereCast) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(Vector3, float, Vector3, RaycastHit*, float, int, int)>(m_PhysicsFunctions.m_SphereCast)(m_vOrigin, m_fRadius, m_vDirection, &m_Hit, m_fMaxDistance, m_iLayerMask, static_cast<int>(m_eQTI));
        }

        int SphereCastNonAlloc(Vector3 m_vOrigin, float m_fRadius, Vector3 m_vDirection, il2cppArray<RaycastHit>* m_pResults, float m_fMaxDistance = 1e30f, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_SphereCastNonAlloc || !m_pResults) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(Vector3, float, Vector3, void*, float, int)>(m_PhysicsFunctions.m_SphereCastNonAlloc)(m_vOrigin, m_fRadius, m_vDirection, m_pResults, m_fMaxDistance, m_iLayerMask);
        }

        il2cppArray<CCollider*>* OverlapSphere(Vector3 m_vPosition, float m_fRadius, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_OverlapSphere) return nullptr;
            return reinterpret_cast<il2cppArray<CCollider*>*(UNITY_CALLING_CONVENTION)(Vector3, float, int)>(m_PhysicsFunctions.m_OverlapSphere)(m_vPosition, m_fRadius, m_iLayerMask);
        }

        int OverlapSphereNonAlloc(Vector3 m_vPosition, float m_fRadius, il2cppArray<CCollider*>* m_pResults, int m_iLayerMask = -1)
        {
            if (!m_PhysicsFunctions.m_OverlapSphereNonAlloc || !m_pResults) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(Vector3, float, void*, int)>(m_PhysicsFunctions.m_OverlapSphereNonAlloc)(m_vPosition, m_fRadius, m_pResults, m_iLayerMask);
        }

        bool ComputePenetration(CCollider* m_pColliderA, Vector3 m_vPositionA, Quaternion m_qRotationA, CCollider* m_pColliderB, Vector3 m_vPositionB, Quaternion m_qRotationB, Vector3& m_vDirection, float& m_fDistance)
        {
            if (!m_PhysicsFunctions.m_ComputePenetration) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*, Vector3, Quaternion, void*, Vector3, Quaternion, Vector3*, float*)>(m_PhysicsFunctions.m_ComputePenetration)(m_pColliderA, m_vPositionA, m_qRotationA, m_pColliderB, m_vPositionB, m_qRotationB, &m_vDirection, &m_fDistance);
        }
    }
}
