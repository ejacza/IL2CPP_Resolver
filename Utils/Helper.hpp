#pragma once

#include <vector>
#include <string>
#include <cstdio>

namespace IL2CPP
{
    namespace Helper
    {
        Unity::CComponent* GetMonoBehaviour()
        {
            Unity::il2cppArray<Unity::CGameObject*>* m_Objects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(UNITY_GAMEOBJECT_CLASS);
            for (uintptr_t u = 0U; m_Objects->m_uMaxLength > u; ++u)
            {
                Unity::CGameObject* m_Object = m_Objects->operator[](static_cast<unsigned int>(u));
                if (!m_Object) continue;

                Unity::CComponent* m_MonoBehaviour = m_Object->GetComponentByIndex(UNITY_MONOBEHAVIOUR_CLASS);
                if (m_MonoBehaviour)
                    return m_MonoBehaviour;
            }

            return nullptr;
        }

        static bool IsUnityVersionBelow202120()
        {
            Unity::System_String* verStr = Unity::Application::UnityVersion();
            if (!verStr) return false;
            std::string v = verStr->ToString();
            int major = 0, minor = 0, patch = 0;
            int parsed = std::sscanf(v.c_str(), "%d.%d.%d", &major, &minor, &patch);
            if (parsed < 1 || major == 0) return false;
            if (major != 2021) return major < 2021;
            return minor < 2;
        }

        std::vector<Unity::il2cppObject*> FindObjects(Unity::il2cppClass* klass)
        {
            static bool isBelow202120 = IsUnityVersionBelow202120();

            void* m_pThread = Thread::Attach(Domain::Get());
            struct ThreadGuard {
                void* t;
                ~ThreadGuard() { if (t) Thread::Detach(t); }
            } m_Guard{ m_pThread };

            std::vector<Unity::il2cppObject*> objects;

            using LivenessCallback = void(Unity::il2cppObject**, int, void*);

            auto callback = [](Unity::il2cppObject** arr, int size, void* userdata) {
                auto* vec = reinterpret_cast<std::vector<Unity::il2cppObject*>*>(userdata);
                vec->insert(vec->end(), arr, arr + size);
            };

            if (!Functions.m_UnityLivenessCalculationBegin && !Functions.m_UnityLivenessAllocateStruct)
            {
                auto* arr = Unity::Object::FindObjectsOfType<Unity::il2cppObject>(IL2CPP::Class::GetSystemType(klass), true);
                if (arr)
                {
                    for (uintptr_t i = 0; i < arr->m_uMaxLength; ++i)
                    {
                        if (arr->m_pValues[i])
                            objects.push_back(arr->m_pValues[i]);
                    }
                }
                return objects;
            }

            if (isBelow202120 && Functions.m_UnityLivenessCalculationBegin)
            {
                auto onWorld = [](){};

                auto state = reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(void*, int, LivenessCallback*, void*, void(*)(), void(*)())>(
                    Functions.m_UnityLivenessCalculationBegin
                )(klass, 0, callback, &objects, onWorld, onWorld);

                if (!state) return objects;

                if (Functions.m_UnityLivenessCalculationFromStatics)
                    reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(
                        Functions.m_UnityLivenessCalculationFromStatics
                    )(state);

                if (Functions.m_UnityLivenessCalculationEnd)
                    reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(
                        Functions.m_UnityLivenessCalculationEnd
                    )(state);
            }
            else
            {
                auto realloc = [](void* ptr, size_t size, void*) -> void* {
                    if (ptr && size == 0) {
                        reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_Free)(ptr);
                        return nullptr;
                    }
                    return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(size_t)>(Functions.m_Alloc)(size);
                };

                if (Functions.m_StopGcWorld)
                    reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)()>(Functions.m_StopGcWorld)();

                if (Functions.m_UnityLivenessAllocateStruct)
                {
                    auto state = reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(void*, int, LivenessCallback*, void*, void*(*)(void*, size_t, void*), void*)>(
                        Functions.m_UnityLivenessAllocateStruct
                    )(klass, 0, callback, &objects, realloc, nullptr);

                    if (state)
                    {
                        if (Functions.m_UnityLivenessCalculationFromStatics)
                            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(
                                Functions.m_UnityLivenessCalculationFromStatics
                            )(state);

                        if (Functions.m_UnityLivenessFinalize)
                            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(
                                Functions.m_UnityLivenessFinalize
                            )(state);

                        if (Functions.m_UnityLivenessFreeStruct)
                            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(
                                Functions.m_UnityLivenessFreeStruct
                            )(state);
                    }
                }

                if (Functions.m_StartGcWorld)
                    reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)()>(Functions.m_StartGcWorld)();
            }

            return objects;
        }
    }
}
