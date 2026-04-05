#pragma once

// C Headers
#include <android/log.h>
#include <xdl.h>
#include <unistd.h>
#include <sys/mman.h>

#ifndef LOGI
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "IL2CPP", __VA_ARGS__)
#endif

// C++ Headers
#include <cmath>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <fstream>

#ifndef IL2CPP_ASSERT
    #include <cassert>
    #define IL2CPP_ASSERT(x) assert(x)
#endif

#ifndef IL2CPP_RStr
    #define IL2CPP_RStr(x) x
#endif

#ifndef IL2CPP_MAIN_MODULE
    #define IL2CPP_MAIN_MODULE IL2CPP_RStr("libil2cpp.so")
#endif

#include "Defines.hpp"
#include "Unity/Structures/Vector2.hpp"
#include "Unity/Structures/Vector3.hpp"
#include "Unity/Structures/Vector4.hpp"
#include "Unity/Structures/Quaternion.hpp"
#include "Unity/Structures/Matrix3x3.hpp"
#include "Unity/Structures/Matrix4x4.hpp"
#include "Unity/Structures/Rect.hpp"
#include "Unity/Structures/Color.hpp"
#include "Data.hpp"
#include "Unity/Obfuscators.hpp"
#include "Unity/Defines.hpp"
#include "Unity/Structures/il2cpp.hpp"
#include "Unity/Structures/il2cppArray.hpp"
#include "Unity/Structures/il2cppDictionary.hpp"
#include "Unity/Structures/Engine.hpp"
#include "Unity/Structures/System_String.hpp"
#include "Utils/Hash.hpp"
#include "Utils/VTable.hpp"
#include "API/Domain.hpp"
#include "API/Class.hpp"
#include "API/ResolveCall.hpp"
#include "API/String.hpp"
#include "API/Thread.hpp"
#include "SystemTypeCache.hpp"

namespace Unity
{
    class CCamera;
    class CComponent;
    class CGameObject;
    class CLayerMask;
    class CObject;
    class CRigidbody;
    class CTransform;
    class CPhysics;
}

#include "Unity/API/Application.hpp"
#include "Unity/API/Time.hpp"
#include "Unity/API/Object.hpp"
#include "Unity/API/GameObject.hpp"
#include "Unity/API/Camera.hpp"
#include "Unity/API/Component.hpp"
#include "Unity/API/LayerMask.hpp"
#include "Unity/API/Rigidbody.hpp"
#include "Unity/API/Transform.hpp"
#include "Unity/API/Physics.hpp"
#include "Unity/API/Screen.hpp"
#include "Unity/API/Shader.hpp"
#include "Unity/API/Material.hpp"
#include "Unity/API/Renderer.hpp"

#include "Utils/Helper.hpp"
#include "Dumper.hpp"

namespace IL2CPP
{
    namespace UnityAPI
    {
        enum m_eExportObfuscationType
        {
            None = 0,
            ROT  = 1,
            XOR  = 2,
            MAX  = 3,
        };

        m_eExportObfuscationType m_ExportObfuscation = m_eExportObfuscationType::None;
        int m_ROTObfuscationValue = -1;
        int m_XORObfuscationKey = -1;

        static const char* s_DetectionSymbols[] = {
            IL2CPP_INIT_EXPORT,
            IL2CPP_DOMAIN_GET_EXPORT,
            IL2CPP_CLASS_GET_NAME_EXPORT,
            nullptr,
        };

        void* ResolveExport(const char* m_Name)
        {
            switch (m_ExportObfuscation)
            {
                case m_eExportObfuscationType::ROT:
                {
                    if (m_ROTObfuscationValue == -1)
                    {
                        char m_Buffer[256];
                        for (int i = 1; 26 > i; ++i)
                        {
                            strncpy(m_Buffer, m_Name, sizeof(m_Buffer) - 1);
                            m_Buffer[sizeof(m_Buffer) - 1] = '\0';
                            Unity::Obfuscators::ROT_String_InPlace(m_Buffer, i);
                            void* m_Return = xdl_sym(Globals.m_GameAssembly, m_Buffer, nullptr);
                            if (m_Return) { m_ROTObfuscationValue = i; return m_Return; }
                        }
                        return nullptr;
                    }
                    char m_Buffer[256];
                    strncpy(m_Buffer, m_Name, sizeof(m_Buffer) - 1);
                    m_Buffer[sizeof(m_Buffer) - 1] = '\0';
                    Unity::Obfuscators::ROT_String_InPlace(m_Buffer, m_ROTObfuscationValue);
                    return xdl_sym(Globals.m_GameAssembly, m_Buffer, nullptr);
                }
                case m_eExportObfuscationType::XOR:
                {
                    if (m_XORObfuscationKey == -1)
                    {
                        char m_Buffer[256];
                        for (int i = 1; 256 > i; ++i)
                        {
                            strncpy(m_Buffer, m_Name, sizeof(m_Buffer) - 1);
                            m_Buffer[sizeof(m_Buffer) - 1] = '\0';
                            Unity::Obfuscators::XOR_String_InPlace(m_Buffer, i);
                            void* m_Return = xdl_sym(Globals.m_GameAssembly, m_Buffer, nullptr);
                            if (m_Return) { m_XORObfuscationKey = i; return m_Return; }
                        }
                        return nullptr;
                    }
                    char m_Buffer[256];
                    strncpy(m_Buffer, m_Name, sizeof(m_Buffer) - 1);
                    m_Buffer[sizeof(m_Buffer) - 1] = '\0';
                    Unity::Obfuscators::XOR_String_InPlace(m_Buffer, m_XORObfuscationKey);
                    return xdl_sym(Globals.m_GameAssembly, m_Buffer, nullptr);
                }
                default:
                    return xdl_sym(Globals.m_GameAssembly, m_Name, nullptr);
            }
            return nullptr;
        }

        bool ResolveExport_Boolean(void** m_Address, const char* m_Name)
        {
            *m_Address = ResolveExport(m_Name);
            return true;
        }

        bool Initialize()
        {
            bool m_InitExportResolved = false;
            for (int i = 0; m_eExportObfuscationType::MAX > i; ++i)
            {
                m_ExportObfuscation = static_cast<m_eExportObfuscationType>(i);
                if (ResolveExport(IL2CPP_INIT_EXPORT)) { m_InitExportResolved = true; break; }
            }

            IL2CPP_ASSERT(m_InitExportResolved && "Couldn't resolve il2cpp_init!");
            if (!m_InitExportResolved) return false;

            if (m_ExportObfuscation != m_eExportObfuscationType::None)
            {
                int m_ConfirmedCount = 0;
                for (int i = 1; s_DetectionSymbols[i] != nullptr; ++i)
                {
                    if (ResolveExport(s_DetectionSymbols[i]))
                        ++m_ConfirmedCount;
                }

                if (m_ConfirmedCount == 0)
                {
                    m_ExportObfuscation = m_eExportObfuscationType::None;
                    m_ROTObfuscationValue = -1;
                    m_XORObfuscationKey = -1;
                    LOGI("Obfuscation detection failed, falling back to None");
                }
                else
                {
                    LOGI("Obfuscation detected: type=%d, ROT=%d, XOR=%d",
                         m_ExportObfuscation, m_ROTObfuscationValue, m_XORObfuscationKey);
                }
            }

            std::unordered_map<const char*, void**> m_ExportMap =
            {
                { IL2CPP_ADD_INTERNAL_CALL_EXPORT                              , &Functions.m_AddInternalCall },
                { IL2CPP_ALLOC_EXPORT                                          , &Functions.m_Alloc },
                { IL2CPP_ALLOCATION_GRANULARITY_EXPORT                         , &Functions.m_AllocationGranularity },
                { IL2CPP_ARRAY_CLASS_GET_EXPORT                                , &Functions.m_ArrayClassGet },
                { IL2CPP_ARRAY_ELEMENT_SIZE_EXPORT                             , &Functions.m_ArrayElementSize },
                { IL2CPP_ARRAY_GET_BYTE_LENGTH_EXPORT                          , &Functions.m_ArrayGetByteLength },
                { IL2CPP_ARRAY_LENGTH_EXPORT                                   , &Functions.m_ArrayLength },
                { IL2CPP_ARRAY_NEW_EXPORT                                      , &Functions.m_ArrayNew },
                { IL2CPP_ARRAY_NEW_FULL_EXPORT                                 , &Functions.m_ArrayNewFull },
                { IL2CPP_ARRAY_NEW_SPECIFIC_EXPORT                             , &Functions.m_ArrayNewSpecific },
                { IL2CPP_ARRAY_OBJECT_HEADER_SIZE_EXPORT                       , &Functions.m_ArrayObjectHeaderSize },
                { IL2CPP_ASSEMBLY_GET_IMAGE_EXPORT                             , &Functions.m_AssemblyGetImage },
                { IL2CPP_BOUNDED_ARRAY_CLASS_GET_EXPORT                        , &Functions.m_BoundedArrayClassGet },
                { IL2CPP_CAPTURE_MEMORY_SNAPSHOT_EXPORT                        , &Functions.m_CaptureMemorySnapshot },
                { IL2CPP_CLASS_ARRAY_ELEMENT_SIZE_EXPORT                       , &Functions.m_ClassArrayElementSize },
                { IL2CPP_CLASS_ENUM_BASETYPE_EXPORT                            , &Functions.m_ClassEnumBasetype },
                { IL2CPP_CLASS_FOR_EACH_EXPORT                                 , &Functions.m_ClassForEach },
                { IL2CPP_CLASS_FROM_IL2CPP_TYPE_EXPORT                         , &Functions.m_ClassFromIl2cppType },
                { IL2CPP_CLASS_FROM_NAME_EXPORT                                , &Functions.m_ClassFromName },
                { IL2CPP_CLASS_FROM_SYSTEM_TYPE_EXPORT                         , &Functions.m_ClassFromSystemType },
                { IL2CPP_CLASS_FROM_TYPE_EXPORT                                , &Functions.m_ClassFromType },
                { IL2CPP_CLASS_GET_ASSEMBLYNAME_EXPORT                         , &Functions.m_ClassGetAssemblyname },
                { IL2CPP_CLASS_GET_BITMAP_EXPORT                               , &Functions.m_ClassGetBitmap },
                { IL2CPP_CLASS_GET_BITMAP_SIZE_EXPORT                          , &Functions.m_ClassGetBitmapSize },
                { IL2CPP_CLASS_GET_DATA_SIZE_EXPORT                            , &Functions.m_ClassGetDataSize },
                { IL2CPP_CLASS_GET_DECLARING_TYPE_EXPORT                       , &Functions.m_ClassGetDeclaringType },
                { IL2CPP_CLASS_GET_ELEMENT_CLASS_EXPORT                        , &Functions.m_ClassGetElementClass },
                { IL2CPP_CLASS_GET_EVENTS_EXPORT                               , &Functions.m_ClassGetEvents },
                { IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT                      , &Functions.m_ClassGetFieldFromName },
                { IL2CPP_CLASS_GET_FIELDS_EXPORT                               , &Functions.m_ClassGetFields },
                { IL2CPP_CLASS_GET_FLAGS_EXPORT                                , &Functions.m_ClassGetFlags },
                { IL2CPP_CLASS_GET_IMAGE_EXPORT                                , &Functions.m_ClassGetImage },
                { IL2CPP_CLASS_GET_INTERFACES_EXPORT                           , &Functions.m_ClassGetInterfaces },
                { IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT                     , &Functions.m_ClassGetMethodFromName },
                { IL2CPP_CLASS_GET_METHODS_EXPORT                              , &Functions.m_ClassGetMethods },
                { IL2CPP_CLASS_GET_NAME_EXPORT                                 , &Functions.m_ClassGetName },
                { IL2CPP_CLASS_GET_NAMESPACE_EXPORT                            , &Functions.m_ClassGetNamespace },
                { IL2CPP_CLASS_GET_NESTED_TYPES_EXPORT                         , &Functions.m_ClassGetNestedTypes },
                { IL2CPP_CLASS_GET_PARENT_EXPORT                               , &Functions.m_ClassGetParent },
                { IL2CPP_CLASS_GET_PROPERTIES_EXPORT                           , &Functions.m_ClassGetProperties },
                { IL2CPP_CLASS_GET_PROPERTY_FROM_NAME_EXPORT                   , &Functions.m_ClassGetPropertyFromName },
                { IL2CPP_CLASS_GET_RANK_EXPORT                                 , &Functions.m_ClassGetRank },
                { IL2CPP_CLASS_GET_STATIC_FIELD_DATA_EXPORT                    , &Functions.m_ClassGetStaticFieldData },
                { IL2CPP_CLASS_GET_TYPE_EXPORT                                 , &Functions.m_ClassGetType },
                { IL2CPP_CLASS_GET_TYPE_TOKEN_EXPORT                           , &Functions.m_ClassGetTypeToken },
                { IL2CPP_CLASS_GET_USERDATA_OFFSET_EXPORT                      , &Functions.m_ClassGetUserdataOffset },
                { IL2CPP_CLASS_HAS_ATTRIBUTE_EXPORT                            , &Functions.m_ClassHasAttribute },
                { IL2CPP_CLASS_HAS_PARENT_EXPORT                               , &Functions.m_ClassHasParent },
                { IL2CPP_CLASS_HAS_REFERENCES_EXPORT                           , &Functions.m_ClassHasReferences },
                { IL2CPP_CLASS_INSTANCE_SIZE_EXPORT                            , &Functions.m_ClassInstanceSize },
                { IL2CPP_CLASS_IS_ABSTRACT_EXPORT                              , &Functions.m_ClassIsAbstract },
                { IL2CPP_CLASS_IS_ASSIGNABLE_FROM_EXPORT                       , &Functions.m_ClassIsAssignableFrom },
                { IL2CPP_CLASS_IS_BLITTABLE_EXPORT                             , &Functions.m_ClassIsBlittable },
                { IL2CPP_CLASS_IS_ENUM_EXPORT                                  , &Functions.m_ClassIsEnum },
                { IL2CPP_CLASS_IS_GENERIC_EXPORT                               , &Functions.m_ClassIsGeneric },
                { IL2CPP_CLASS_IS_INFLATED_EXPORT                              , &Functions.m_ClassIsInflated },
                { IL2CPP_CLASS_IS_INITED_EXPORT                                , &Functions.m_ClassIsInited },
                { IL2CPP_CLASS_IS_INTERFACE_EXPORT                             , &Functions.m_ClassIsInterface },
                { IL2CPP_CLASS_IS_SUBCLASS_OF_EXPORT                           , &Functions.m_ClassIsSubclassOf },
                { IL2CPP_CLASS_IS_VALUETYPE_EXPORT                             , &Functions.m_ClassIsValuetype },
                { IL2CPP_CLASS_NUM_FIELDS_EXPORT                               , &Functions.m_ClassNumFields },
                { IL2CPP_CLASS_SET_USERDATA_EXPORT                             , &Functions.m_ClassSetUserdata },
                { IL2CPP_CLASS_VALUE_SIZE_EXPORT                               , &Functions.m_ClassValueSize },
                { IL2CPP_CURRENT_THREAD_GET_FRAME_AT_EXPORT                    , &Functions.m_CurrentThreadGetFrameAt },
                { IL2CPP_CURRENT_THREAD_GET_STACK_DEPTH_EXPORT                 , &Functions.m_CurrentThreadGetStackDepth },
                { IL2CPP_CURRENT_THREAD_GET_TOP_FRAME_EXPORT                   , &Functions.m_CurrentThreadGetTopFrame },
                { IL2CPP_CURRENT_THREAD_WALK_FRAME_STACK_EXPORT                , &Functions.m_CurrentThreadWalkFrameStack },
                { IL2CPP_CUSTOM_ATTRS_CONSTRUCT_EXPORT                         , &Functions.m_CustomAttrsConstruct },
                { IL2CPP_CUSTOM_ATTRS_FREE_EXPORT                              , &Functions.m_CustomAttrsFree },
                { IL2CPP_CUSTOM_ATTRS_FROM_CLASS_EXPORT                        , &Functions.m_CustomAttrsFromClass },
                { IL2CPP_CUSTOM_ATTRS_FROM_FIELD_EXPORT                        , &Functions.m_CustomAttrsFromField },
                { IL2CPP_CUSTOM_ATTRS_FROM_METHOD_EXPORT                       , &Functions.m_CustomAttrsFromMethod },
                { IL2CPP_CUSTOM_ATTRS_GET_ATTR_EXPORT                          , &Functions.m_CustomAttrsGetAttr },
                { IL2CPP_CUSTOM_ATTRS_HAS_ATTR_EXPORT                          , &Functions.m_CustomAttrsHasAttr },
                { IL2CPP_DEBUG_GET_METHOD_INFO_EXPORT                          , &Functions.m_DebugGetMethodInfo },
                { IL2CPP_DEBUGGER_SET_AGENT_OPTIONS_EXPORT                     , &Functions.m_DebuggerSetAgentOptions },
                { IL2CPP_DOMAIN_ASSEMBLY_OPEN_EXPORT                           , &Functions.m_DomainAssemblyOpen },
                { IL2CPP_DOMAIN_GET_EXPORT                                     , &Functions.m_DomainGet },
                { IL2CPP_DOMAIN_GET_ASSEMBLIES_EXPORT                          , &Functions.m_DomainGetAssemblies },
                { IL2CPP_EXCEPTION_FROM_NAME_MSG_EXPORT                        , &Functions.m_ExceptionFromNameMsg },
                { IL2CPP_FIELD_GET_FLAGS_EXPORT                                , &Functions.m_FieldGetFlags },
                { IL2CPP_FIELD_GET_NAME_EXPORT                                 , &Functions.m_FieldGetName },
                { IL2CPP_FIELD_GET_OFFSET_EXPORT                               , &Functions.m_FieldGetOffset },
                { IL2CPP_FIELD_GET_PARENT_EXPORT                               , &Functions.m_FieldGetParent },
                { IL2CPP_FIELD_GET_TYPE_EXPORT                                 , &Functions.m_FieldGetType },
                { IL2CPP_FIELD_GET_VALUE_EXPORT                                , &Functions.m_FieldGetValue },
                { IL2CPP_FIELD_GET_VALUE_OBJECT_EXPORT                         , &Functions.m_FieldGetValueObject },
                { IL2CPP_FIELD_HAS_ATTRIBUTE_EXPORT                            , &Functions.m_FieldHasAttribute },
                { IL2CPP_FIELD_IS_LITERAL_EXPORT                               , &Functions.m_FieldIsLiteral },
                { IL2CPP_FIELD_SET_VALUE_EXPORT                                , &Functions.m_FieldSetValue },
                { IL2CPP_FIELD_SET_VALUE_OBJECT_EXPORT                         , &Functions.m_FieldSetValueObject },
                { IL2CPP_FIELD_STATIC_GET_VALUE_EXPORT                         , &Functions.m_FieldStaticGetValue },
                { IL2CPP_FIELD_STATIC_SET_VALUE_EXPORT                         , &Functions.m_FieldStaticSetValue },
                { IL2CPP_FORMAT_EXCEPTION_EXPORT                               , &Functions.m_FormatException },
                { IL2CPP_FORMAT_STACK_TRACE_EXPORT                             , &Functions.m_FormatStackTrace },
                { IL2CPP_FREE_EXPORT                                           , &Functions.m_Free },
                { IL2CPP_FREE_CAPTURED_MEMORY_SNAPSHOT_EXPORT                  , &Functions.m_FreeCapturedMemorySnapshot },
                { IL2CPP_GC_ALLOC_FIXED_EXPORT                                 , &Functions.m_GcAllocFixed },
                { IL2CPP_GC_COLLECT_EXPORT                                     , &Functions.m_GcCollect },
                { IL2CPP_GC_COLLECT_A_LITTLE_EXPORT                            , &Functions.m_GcCollectALittle },
                { IL2CPP_GC_DISABLE_EXPORT                                     , &Functions.m_GcDisable },
                { IL2CPP_GC_ENABLE_EXPORT                                      , &Functions.m_GcEnable },
                { IL2CPP_GC_FOREACH_HEAP_EXPORT                                , &Functions.m_GcForeachHeap },
                { IL2CPP_GC_FREE_FIXED_EXPORT                                  , &Functions.m_GcFreeFixed },
                { IL2CPP_GC_GET_HEAP_SIZE_EXPORT                               , &Functions.m_GcGetHeapSize },
                { IL2CPP_GC_GET_MAX_TIME_SLICE_NS_EXPORT                       , &Functions.m_GcGetMaxTimeSliceNs },
                { IL2CPP_GC_GET_USED_SIZE_EXPORT                               , &Functions.m_GcGetUsedSize },
                { IL2CPP_GC_HAS_STRICT_WBARRIERS_EXPORT                        , &Functions.m_GcHasStrictWbarriers },
                { IL2CPP_GC_IS_DISABLED_EXPORT                                 , &Functions.m_GcIsDisabled },
                { IL2CPP_GC_IS_INCREMENTAL_EXPORT                              , &Functions.m_GcIsIncremental },
                { IL2CPP_GC_SET_EXTERNAL_ALLOCATION_TRACKER_EXPORT             , &Functions.m_GcSetExternalAllocationTracker },
                { IL2CPP_GC_SET_EXTERNAL_WBARRIER_TRACKER_EXPORT               , &Functions.m_GcSetExternalWbarrierTracker },
                { IL2CPP_GC_SET_MAX_TIME_SLICE_NS_EXPORT                       , &Functions.m_GcSetMaxTimeSliceNs },
                { IL2CPP_GC_SET_MODE_EXPORT                                    , &Functions.m_GcSetMode },
                { IL2CPP_GC_START_INCREMENTAL_COLLECTION_EXPORT                , &Functions.m_GcStartIncrementalCollection },
                { IL2CPP_GC_WBARRIER_SET_FIELD_EXPORT                          , &Functions.m_GcWbarrierSetField },
                { IL2CPP_GCHANDLE_FOREACH_GET_TARGET_EXPORT                    , &Functions.m_GchandleForeachGetTarget },
                { IL2CPP_GCHANDLE_FREE_EXPORT                                  , &Functions.m_GchandleFree },
                { IL2CPP_GCHANDLE_GET_TARGET_EXPORT                            , &Functions.m_GchandleGetTarget },
                { IL2CPP_GCHANDLE_NEW_EXPORT                                   , &Functions.m_GchandleNew },
                { IL2CPP_GCHANDLE_NEW_WEAKREF_EXPORT                           , &Functions.m_GchandleNewWeakref },
                { IL2CPP_GET_CORLIB_EXPORT                                     , &Functions.m_GetCorlib },
                { IL2CPP_GET_EXCEPTION_ARGUMENT_NULL_EXPORT                    , &Functions.m_GetExceptionArgumentNull },
                { IL2CPP_IMAGE_GET_ASSEMBLY_EXPORT                             , &Functions.m_ImageGetAssembly },
                { IL2CPP_IMAGE_GET_CLASS_EXPORT                                , &Functions.m_ImageGetClass },
                { IL2CPP_IMAGE_GET_CLASS_COUNT_EXPORT                          , &Functions.m_ImageGetClassCount },
                { IL2CPP_IMAGE_GET_ENTRY_POINT_EXPORT                          , &Functions.m_ImageGetEntryPoint },
                { IL2CPP_IMAGE_GET_FILENAME_EXPORT                             , &Functions.m_ImageGetFilename },
                { IL2CPP_IMAGE_GET_NAME_EXPORT                                 , &Functions.m_ImageGetName },
                { IL2CPP_INIT_EXPORT                                           , &Functions.m_Init },
                { IL2CPP_INIT_UTF16_EXPORT                                     , &Functions.m_InitUtf16 },
                { IL2CPP_IS_DEBUGGER_ATTACHED_EXPORT                           , &Functions.m_IsDebuggerAttached },
                { IL2CPP_IS_VM_THREAD_EXPORT                                   , &Functions.m_IsVmThread },
                { IL2CPP_MEMORY_POOL_GET_REGION_SIZE_EXPORT                    , &Functions.m_MemoryPoolGetRegionSize },
                { IL2CPP_MEMORY_POOL_SET_REGION_SIZE_EXPORT                    , &Functions.m_MemoryPoolSetRegionSize },
                { IL2CPP_METHOD_GET_CLASS_EXPORT                               , &Functions.m_MethodGetClass },
                { IL2CPP_METHOD_GET_DECLARING_TYPE_EXPORT                      , &Functions.m_MethodGetDeclaringType },
                { IL2CPP_METHOD_GET_FLAGS_EXPORT                               , &Functions.m_MethodGetFlags },
                { IL2CPP_METHOD_GET_FROM_REFLECTION_EXPORT                     , &Functions.m_MethodGetFromReflection },
                { IL2CPP_METHOD_GET_NAME_EXPORT                                , &Functions.m_MethodGetName },
                { IL2CPP_METHOD_GET_OBJECT_EXPORT                              , &Functions.m_MethodGetObject },
                { IL2CPP_METHOD_GET_PARAM_EXPORT                               , &Functions.m_MethodGetParam },
                { IL2CPP_METHOD_GET_PARAM_COUNT_EXPORT                         , &Functions.m_MethodGetParamCount },
                { IL2CPP_METHOD_GET_PARAM_NAME_EXPORT                          , &Functions.m_MethodGetParamName },
                { IL2CPP_METHOD_GET_RETURN_TYPE_EXPORT                         , &Functions.m_MethodGetReturnType },
                { IL2CPP_METHOD_GET_TOKEN_EXPORT                               , &Functions.m_MethodGetToken },
                { IL2CPP_METHOD_HAS_ATTRIBUTE_EXPORT                           , &Functions.m_MethodHasAttribute },
                { IL2CPP_METHOD_IS_GENERIC_EXPORT                              , &Functions.m_MethodIsGeneric },
                { IL2CPP_METHOD_IS_INFLATED_EXPORT                             , &Functions.m_MethodIsInflated },
                { IL2CPP_METHOD_IS_INSTANCE_EXPORT                             , &Functions.m_MethodIsInstance },
                { IL2CPP_MONITOR_ENTER_EXPORT                                  , &Functions.m_MonitorEnter },
                { IL2CPP_MONITOR_EXIT_EXPORT                                   , &Functions.m_MonitorExit },
                { IL2CPP_MONITOR_PULSE_EXPORT                                  , &Functions.m_MonitorPulse },
                { IL2CPP_MONITOR_PULSE_ALL_EXPORT                              , &Functions.m_MonitorPulseAll },
                { IL2CPP_MONITOR_TRY_ENTER_EXPORT                              , &Functions.m_MonitorTryEnter },
                { IL2CPP_MONITOR_TRY_WAIT_EXPORT                               , &Functions.m_MonitorTryWait },
                { IL2CPP_MONITOR_WAIT_EXPORT                                   , &Functions.m_MonitorWait },
                { IL2CPP_NATIVE_STACK_TRACE_EXPORT                             , &Functions.m_NativeStackTrace },
                { IL2CPP_OBJECT_GET_CLASS_EXPORT                               , &Functions.m_ObjectGetClass },
                { IL2CPP_OBJECT_GET_SIZE_EXPORT                                , &Functions.m_ObjectGetSize },
                { IL2CPP_OBJECT_GET_VIRTUAL_METHOD_EXPORT                      , &Functions.m_ObjectGetVirtualMethod },
                { IL2CPP_OBJECT_HEADER_SIZE_EXPORT                             , &Functions.m_ObjectHeaderSize },
                { IL2CPP_OBJECT_NEW_EXPORT                                     , &Functions.m_pObjectNew },
                { IL2CPP_OBJECT_UNBOX_EXPORT                                   , &Functions.m_ObjectUnbox },
                { IL2CPP_OFFSET_OF_ARRAY_BOUNDS_IN_ARRAY_OBJECT_HEADER_EXPORT  , &Functions.m_OffsetOfArrayBoundsInArrayObjectHeader },
                { IL2CPP_OFFSET_OF_ARRAY_LENGTH_IN_ARRAY_OBJECT_HEADER_EXPORT  , &Functions.m_OffsetOfArrayLengthInArrayObjectHeader },
                { IL2CPP_OVERRIDE_STACK_BACKTRACE_EXPORT                       , &Functions.m_OverrideStackBacktrace },
                { IL2CPP_PROFILER_INSTALL_EXPORT                               , &Functions.m_ProfilerInstall },
                { IL2CPP_PROFILER_INSTALL_ALLOCATION_EXPORT                    , &Functions.m_ProfilerInstallAllocation },
                { IL2CPP_PROFILER_INSTALL_ENTER_LEAVE_EXPORT                   , &Functions.m_ProfilerInstallEnterLeave },
                { IL2CPP_PROFILER_INSTALL_FILEIO_EXPORT                        , &Functions.m_ProfilerInstallFileio },
                { IL2CPP_PROFILER_INSTALL_GC_EXPORT                            , &Functions.m_ProfilerInstallGc },
                { IL2CPP_PROFILER_INSTALL_THREAD_EXPORT                        , &Functions.m_ProfilerInstallThread },
                { IL2CPP_PROFILER_SET_EVENTS_EXPORT                            , &Functions.m_ProfilerSetEvents },
                { IL2CPP_PROPERTY_GET_FLAGS_EXPORT                             , &Functions.m_PropertyGetFlags },
                { IL2CPP_PROPERTY_GET_GET_METHOD_EXPORT                        , &Functions.m_PropertyGetGetMethod },
                { IL2CPP_PROPERTY_GET_NAME_EXPORT                              , &Functions.m_PropertyGetName },
                { IL2CPP_PROPERTY_GET_PARENT_EXPORT                            , &Functions.m_PropertyGetParent },
                { IL2CPP_PROPERTY_GET_SET_METHOD_EXPORT                        , &Functions.m_PropertyGetSetMethod },
                { IL2CPP_RAISE_EXCEPTION_EXPORT                                , &Functions.m_RaiseException },
                { IL2CPP_REGISTER_DEBUGGER_AGENT_TRANSPORT_EXPORT              , &Functions.m_RegisterDebuggerAgentTransport },
                { IL2CPP_REGISTER_LOG_CALLBACK_EXPORT                          , &Functions.m_RegisterLogCallback },
                { IL2CPP_RESOLVE_ICALL_EXPORT                                  , &Functions.m_ResolveFunction },
                { IL2CPP_RUNTIME_CLASS_INIT_EXPORT                             , &Functions.m_RuntimeClassInit },
                { IL2CPP_RUNTIME_INVOKE_EXPORT                                 , &Functions.m_RuntimeInvoke },
                { IL2CPP_RUNTIME_INVOKE_CONVERT_ARGS_EXPORT                    , &Functions.m_RuntimeInvokeConvertArgs },
                { IL2CPP_RUNTIME_OBJECT_INIT_EXPORT                            , &Functions.m_RuntimeObjectInit },
                { IL2CPP_RUNTIME_OBJECT_INIT_EXCEPTION_EXPORT                  , &Functions.m_RuntimeObjectInitException },
                { IL2CPP_RUNTIME_UNHANDLED_EXCEPTION_POLICY_SET_EXPORT         , &Functions.m_RuntimeUnhandledExceptionPolicySet },
                { IL2CPP_SET_COMMANDLINE_ARGUMENTS_EXPORT                      , &Functions.m_SetCommandlineArguments },
                { IL2CPP_SET_COMMANDLINE_ARGUMENTS_UTF16_EXPORT                , &Functions.m_SetCommandlineArgumentsUtf16 },
                { IL2CPP_SET_CONFIG_EXPORT                                     , &Functions.m_SetConfig },
                { IL2CPP_SET_CONFIG_DIR_EXPORT                                 , &Functions.m_SetConfigDir },
                { IL2CPP_SET_CONFIG_UTF16_EXPORT                               , &Functions.m_SetConfigUtf16 },
                { IL2CPP_SET_DATA_DIR_EXPORT                                   , &Functions.m_SetDataDir },
                { IL2CPP_SET_DEFAULT_THREAD_AFFINITY_EXPORT                    , &Functions.m_SetDefaultThreadAffinity },
                { IL2CPP_SET_FIND_PLUGIN_CALLBACK_EXPORT                       , &Functions.m_SetFindPluginCallback },
                { IL2CPP_SET_MEMORY_CALLBACKS_EXPORT                           , &Functions.m_SetMemoryCallbacks },
                { IL2CPP_SET_TEMP_DIR_EXPORT                                   , &Functions.m_SetTempDir },
                { IL2CPP_SHUTDOWN_EXPORT                                       , &Functions.m_Shutdown },
                { IL2CPP_START_GC_WORLD_EXPORT                                 , &Functions.m_StartGcWorld },
                { IL2CPP_STATS_DUMP_TO_FILE_EXPORT                             , &Functions.m_StatsDumpToFile },
                { IL2CPP_STATS_GET_VALUE_EXPORT                                , &Functions.m_StatsGetValue },
                { IL2CPP_STOP_GC_WORLD_EXPORT                                  , &Functions.m_StopGcWorld },
                { IL2CPP_STRING_CHARS_EXPORT                                   , &Functions.m_StringChars },
                { IL2CPP_STRING_INTERN_EXPORT                                  , &Functions.m_StringIntern },
                { IL2CPP_STRING_IS_INTERNED_EXPORT                             , &Functions.m_StringIsInterned },
                { IL2CPP_STRING_LENGTH_EXPORT                                  , &Functions.m_StringLength },
                { IL2CPP_STRING_NEW_EXPORT                                     , &Functions.m_StringNew },
                { IL2CPP_STRING_NEW_LEN_EXPORT                                 , &Functions.m_StringNewLen },
                { IL2CPP_STRING_NEW_UTF16_EXPORT                               , &Functions.m_StringNewUtf16 },
                { IL2CPP_STRING_NEW_WRAPPER_EXPORT                             , &Functions.m_StringNewWrapper },
                { IL2CPP_THREAD_ATTACH_EXPORT                                  , &Functions.m_ThreadAttach },
                { IL2CPP_THREAD_CURRENT_EXPORT                                 , &Functions.m_ThreadCurrent },
                { IL2CPP_THREAD_DETACH_EXPORT                                  , &Functions.m_ThreadDetach },
                { IL2CPP_THREAD_GET_ALL_ATTACHED_THREADS_EXPORT                , &Functions.m_ThreadGetAllAttachedThreads },
                { IL2CPP_THREAD_GET_FRAME_AT_EXPORT                            , &Functions.m_ThreadGetFrameAt },
                { IL2CPP_THREAD_GET_STACK_DEPTH_EXPORT                         , &Functions.m_ThreadGetStackDepth },
                { IL2CPP_THREAD_GET_TOP_FRAME_EXPORT                           , &Functions.m_ThreadGetTopFrame },
                { IL2CPP_THREAD_WALK_FRAME_STACK_EXPORT                        , &Functions.m_ThreadWalkFrameStack },
                { IL2CPP_TYPE_EQUALS_EXPORT                                    , &Functions.m_TypeEquals },
                { IL2CPP_TYPE_GET_ASSEMBLY_QUALIFIED_NAME_EXPORT               , &Functions.m_TypeGetAssemblyQualifiedName },
                { IL2CPP_TYPE_GET_ATTRS_EXPORT                                 , &Functions.m_TypeGetAttrs },
                { IL2CPP_TYPE_GET_CLASS_OR_ELEMENT_CLASS_EXPORT                , &Functions.m_TypeGetClassOrElementClass },
                { IL2CPP_TYPE_GET_NAME_EXPORT                                  , &Functions.m_TypeGetName },
                { IL2CPP_TYPE_GET_NAME_CHUNKED_EXPORT                          , &Functions.m_TypeGetNameChunked },
                { IL2CPP_TYPE_GET_OBJECT_EXPORT                                , &Functions.m_TypeGetObject },
                { IL2CPP_TYPE_GET_REFLECTION_NAME_EXPORT                       , &Functions.m_TypeGetReflectionName },
                { IL2CPP_TYPE_GET_TYPE_EXPORT                                  , &Functions.m_TypeGetType },
                { IL2CPP_TYPE_IS_BYREF_EXPORT                                  , &Functions.m_TypeIsByref },
                { IL2CPP_TYPE_IS_POINTER_TYPE_EXPORT                           , &Functions.m_TypeIsPointerType },
                { IL2CPP_TYPE_IS_STATIC_EXPORT                                 , &Functions.m_TypeIsStatic },
                { IL2CPP_UNHANDLED_EXCEPTION_EXPORT                            , &Functions.m_UnhandledException },
                { IL2CPP_UNITY_INSTALL_UNITYTLS_INTERFACE_EXPORT               , &Functions.m_UnityInstallUnitytlsInterface },
                { IL2CPP_UNITY_LIVENESS_ALLOCATE_STRUCT_EXPORT                 , &Functions.m_UnityLivenessAllocateStruct },
                { IL2CPP_UNITY_LIVENESS_CALCULATION_BEGIN_EXPORT               , &Functions.m_UnityLivenessCalculationBegin },
                { IL2CPP_UNITY_LIVENESS_CALCULATION_END_EXPORT                 , &Functions.m_UnityLivenessCalculationEnd },
                { IL2CPP_UNITY_LIVENESS_CALCULATION_FROM_ROOT_EXPORT           , &Functions.m_UnityLivenessCalculationFromRoot },
                { IL2CPP_UNITY_LIVENESS_CALCULATION_FROM_STATICS_EXPORT        , &Functions.m_UnityLivenessCalculationFromStatics },
                { IL2CPP_UNITY_LIVENESS_FINALIZE_EXPORT                        , &Functions.m_UnityLivenessFinalize },
                { IL2CPP_UNITY_LIVENESS_FREE_STRUCT_EXPORT                     , &Functions.m_UnityLivenessFreeStruct },
                { IL2CPP_UNITY_SET_ANDROID_NETWORK_UP_STATE_FUNC_EXPORT        , &Functions.m_UnitySetAndroidNetworkUpStateFunc },
                { IL2CPP_VALUE_BOX_EXPORT                                      , &Functions.m_ValueBox },
            };

            for (auto& m_ExportPair : m_ExportMap)
            {
                if (!ResolveExport_Boolean(m_ExportPair.second, &m_ExportPair.first[0]))
                    return false;
            }

            Unity::Application::Initialize();
            Unity::Time::Initialize();
            Unity::Object::Initialize();
            Unity::GameObject::Initialize();
            Unity::Camera::Initialize();
            Unity::Component::Initialize();
            Unity::LayerMask::Initialize();
            Unity::RigidBody::Initialize();
            Unity::Transform::Initialize();
            Unity::Physics::Initialize();
            Unity::Screen::Initialize();
            Unity::Shader::Initialize();
            Unity::Material::Initialize();
            Unity::Renderer::Initialize();

            IL2CPP::SystemTypeCache::Initializer::PreCache();

            return true;
        }
    }

    bool IsLibraryLoaded(const char* libName)
    {
        std::ifstream maps("/proc/self/maps");
        std::string line;
        while (std::getline(maps, line)) {
            if (line.find(libName) != std::string::npos)
                return true;
        }
        return false;
    }

    bool Initialize(bool m_WaitForModule = false, int m_MaxSecondsWait = 60)
    {
        if (m_WaitForModule)
        {
            LOGI("Waiting for %s...", IL2CPP_MAIN_MODULE);
            while (!IsLibraryLoaded(IL2CPP_MAIN_MODULE))
                usleep(100000);

            LOGI("%s found, waiting for init...", IL2CPP_MAIN_MODULE);
            usleep(500000);

            int m_SecondsWaited = 0;
            while (!Globals.m_GameAssembly)
            {
                if (m_SecondsWaited >= m_MaxSecondsWait) return false;
                Globals.m_GameAssembly = xdl_open(IL2CPP_MAIN_MODULE, XDL_DEFAULT);
                ++m_SecondsWaited;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else
            Globals.m_GameAssembly = xdl_open(IL2CPP_MAIN_MODULE, XDL_DEFAULT);

        if (!Globals.m_GameAssembly || !UnityAPI::Initialize()) return false;
        return true;
    }

    bool Initialize(void* GameAssemblyHandle)
    {
        if (!GameAssemblyHandle) return false;
        Globals.m_GameAssembly = GameAssemblyHandle;
        if (!UnityAPI::Initialize()) return false;
        return true;
    }
}