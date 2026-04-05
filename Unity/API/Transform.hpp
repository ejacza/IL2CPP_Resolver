#pragma once

namespace Unity
{
    struct TransformFunctions_t
    {
        void* m_GetParent = nullptr;
        void* m_GetRoot = nullptr;
        void* m_GetChild = nullptr;
        void* m_GetChildCount = nullptr;
        void* m_FindChild = nullptr;
        void* m_GetPosition = nullptr;
        void* m_GetRotation = nullptr;
        void* m_GetLocalPosition = nullptr;
        void* m_GetLocalScale = nullptr;
        void* m_SetPosition = nullptr;
        void* m_SetRotation = nullptr;
        void* m_SetLocalPosition = nullptr;
        void* m_SetLocalScale = nullptr;
    };
    TransformFunctions_t m_TransformFunctions;

    class CTransform : public IL2CPP::CClass
    {
    public:
        CTransform* GetParent()
        {
            if (!m_TransformFunctions.m_GetParent) return nullptr;
            return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(m_TransformFunctions.m_GetParent)(this);
        }

        CTransform* GetRoot()
        {
            if (!m_TransformFunctions.m_GetRoot) return nullptr;
            return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(m_TransformFunctions.m_GetRoot)(this);
        }

        CTransform* GetChild(int m_iIndex)
        {
            if (!m_TransformFunctions.m_GetChild) return nullptr;
            return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*, int)>(m_TransformFunctions.m_GetChild)(this, m_iIndex);
        }

        int GetChildCount()
        {
            if (!m_TransformFunctions.m_GetChildCount) return 0;
            return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(void*)>(m_TransformFunctions.m_GetChildCount)(this);
        }

        CTransform* FindChild(const char* path, bool isActiveOnly)
        {
            if (!m_TransformFunctions.m_FindChild) return nullptr;
            return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*, System_String*, bool)>(m_TransformFunctions.m_FindChild)(this, IL2CPP::String::New(path), isActiveOnly);
        }

        CTransform* FindChild(const char* path)
        {
            if (!path) return nullptr;
            return FindChild(path, false);
        }

        Vector3 GetPosition()
        {
            Vector3 vRet;
            if (!m_TransformFunctions.m_GetPosition) return vRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(m_TransformFunctions.m_GetPosition)(this, vRet);
            return vRet;
        }

        Vector3 GetForward()
        {
            return GetRotation() * Vector3{ 0.f, 0.f, 1.f };
        }

        Quaternion GetRotation()
        {
            Quaternion m_qRet;
            if (!m_TransformFunctions.m_GetRotation) return m_qRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Quaternion&)>(m_TransformFunctions.m_GetRotation)(this, m_qRet);
            return m_qRet;
        }

        Vector3 GetLocalPosition()
        {
            Vector3 vRet;
            if (!m_TransformFunctions.m_GetLocalPosition) return vRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(m_TransformFunctions.m_GetLocalPosition)(this, vRet);
            return vRet;
        }

        Vector3 GetLocalScale()
        {
            Vector3 vRet;
            if (!m_TransformFunctions.m_GetLocalScale) return vRet;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(m_TransformFunctions.m_GetLocalScale)(this, vRet);
            return vRet;
        }

        void SetPosition(Vector3 m_vVector)
        {
            if (!m_TransformFunctions.m_SetPosition) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(m_TransformFunctions.m_SetPosition)(this, m_vVector);
        }

        void SetForward(Vector3 m_vVector)
        {
            SetRotation(Quaternion::LookRotation(m_vVector));
        }

        void SetRotation(Quaternion m_qQuat)
        {
            if (!m_TransformFunctions.m_SetRotation) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Quaternion)>(m_TransformFunctions.m_SetRotation)(this, m_qQuat);
        }

        void SetLocalPosition(Vector3 m_vVector)
        {
            if (!m_TransformFunctions.m_SetLocalPosition) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(m_TransformFunctions.m_SetLocalPosition)(this, m_vVector);
        }

        void SetLocalScale(Vector3 m_vVector)
        {
            if (!m_TransformFunctions.m_SetLocalScale) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(m_TransformFunctions.m_SetLocalScale)(this, m_vVector);
        }
    };

    namespace Transform
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_TRANSFORM_CLASS);

            m_TransformFunctions.m_GetParent        = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETPARENT);
            m_TransformFunctions.m_GetRoot          = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETROOT);
            m_TransformFunctions.m_GetChild         = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETCHILD);
            m_TransformFunctions.m_GetChildCount    = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETCHILDCOUNT);
            m_TransformFunctions.m_FindChild        = IL2CPP::ResolveCall(UNITY_TRANSFORM_FINDCHILD);
            m_TransformFunctions.m_GetPosition      = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETPOSITION);
            m_TransformFunctions.m_GetRotation      = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETROTATION);
            m_TransformFunctions.m_GetLocalPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALPOSITION);
            m_TransformFunctions.m_GetLocalScale    = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALSCALE);
            m_TransformFunctions.m_SetPosition      = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETPOSITION);
            m_TransformFunctions.m_SetRotation      = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETROTATION);
            m_TransformFunctions.m_SetLocalPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALPOSITION);
            m_TransformFunctions.m_SetLocalScale    = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALSCALE);
        }
    }
}