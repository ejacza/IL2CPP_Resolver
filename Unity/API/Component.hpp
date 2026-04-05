#pragma once

namespace Unity
{
    struct ComponentFunctions_t
    {
        void* m_GetGameObject = nullptr;
        void* m_GetTransform = nullptr;
        void* m_GetComponent = nullptr;
        void* m_TryGetComponent = nullptr;
        void* m_GetComponentInChildren = nullptr;
        void* m_GetComponentsInChildren = nullptr;
        void* m_GetComponentInParent = nullptr;
        void* m_GetComponents = nullptr;
        void* m_GetTag = nullptr;
    };
    ComponentFunctions_t m_ComponentFunctions;

    class CComponent : public CObject
    {
    public:
        CGameObject* GetGameObject()
        {
            if (!m_ComponentFunctions.m_GetGameObject) return nullptr;
            return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(void*)>(m_ComponentFunctions.m_GetGameObject)(this);
        }

        CTransform* GetTransform()
        {
            if (!m_ComponentFunctions.m_GetTransform) return nullptr;
            return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(m_ComponentFunctions.m_GetTransform)(this);
        }

        CComponent* GetComponent(il2cppObject* type)
        {
            if (!m_ComponentFunctions.m_GetComponent) return nullptr;
            return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, void*)>(m_ComponentFunctions.m_GetComponent)(this, type);
        }

        CComponent* GetComponent(const char* typeName)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return nullptr;
            return GetComponent(IL2CPP::Class::GetSystemType(klass));
        }

        bool TryGetComponent(il2cppObject* type, CComponent** component)
        {
            if (!m_ComponentFunctions.m_TryGetComponent) return false;
            return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*, void*, void**)>(m_ComponentFunctions.m_TryGetComponent)(this, type, reinterpret_cast<void**>(component));
        }

        bool TryGetComponent(const char* typeName, CComponent** component)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return false;
            return TryGetComponent(IL2CPP::Class::GetSystemType(klass), component);
        }

        CComponent* GetComponentInChildren(il2cppObject* type, bool includeInactive)
        {
            if (!m_ComponentFunctions.m_GetComponentInChildren) return nullptr;
            return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, void*, bool)>(m_ComponentFunctions.m_GetComponentInChildren)(this, type, includeInactive);
        }

        CComponent* GetComponentInChildren(const char* typeName, bool includeInactive = true)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return nullptr;
            return GetComponentInChildren(IL2CPP::Class::GetSystemType(klass), includeInactive);
        }

        il2cppArray<CComponent*>* GetComponentsInChildren(il2cppObject* type)
        {
            if (!m_ComponentFunctions.m_GetComponentsInChildren) return nullptr;
            return reinterpret_cast<il2cppArray<CComponent*>*(UNITY_CALLING_CONVENTION)(void*, void*)>(m_ComponentFunctions.m_GetComponentsInChildren)(this, type);
        }

        il2cppArray<CComponent*>* GetComponentsInChildren(const char* typeName)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return nullptr;
            return GetComponentsInChildren(IL2CPP::Class::GetSystemType(klass));
        }

        CComponent* GetComponentInParent(il2cppObject* type, bool includeInactive)
        {
            if (!m_ComponentFunctions.m_GetComponentInParent) return nullptr;
            return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, void*, bool)>(m_ComponentFunctions.m_GetComponentInParent)(this, type, includeInactive);
        }

        CComponent* GetComponentInParent(const char* typeName, bool includeInactive = true)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return nullptr;
            return GetComponentInParent(IL2CPP::Class::GetSystemType(klass), includeInactive);
        }

        void GetComponents(il2cppObject* type, void* results)
        {
            if (!m_ComponentFunctions.m_GetComponents) return;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*, void*)>(m_ComponentFunctions.m_GetComponents)(this, type, results);
        }

        void GetComponents(const char* typeName, void* results)
        {
            il2cppClass* klass = IL2CPP::Class::Find(typeName);
            if (!klass) return;
            GetComponents(IL2CPP::Class::GetSystemType(klass), results);
        }

        System_String* GetTag()
        {
            if (!m_ComponentFunctions.m_GetTag) return nullptr;
            return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ComponentFunctions.m_GetTag)(this);
        }
    };

    namespace Component
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_COMPONENT_CLASS);

            m_ComponentFunctions.m_GetGameObject        = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "get_gameObject");
            m_ComponentFunctions.m_GetTransform         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "get_transform");
            m_ComponentFunctions.m_GetComponent         = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "GetComponent", 1);
            m_ComponentFunctions.m_TryGetComponent      = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "TryGetComponent", 2);
            m_ComponentFunctions.m_GetComponentInChildren = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "GetComponentInChildren", 2);
            m_ComponentFunctions.m_GetComponentsInChildren = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "GetComponentsInChildren", 1);
            m_ComponentFunctions.m_GetComponentInParent   = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "GetComponentInParent", 2);
            m_ComponentFunctions.m_GetComponents          = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "GetComponents", 2);
            m_ComponentFunctions.m_GetTag               = IL2CPP::Class::Utils::GetMethodPointer(UNITY_COMPONENT_CLASS, "get_tag");
        }
    }
}
