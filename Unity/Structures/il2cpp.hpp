#pragma once

#include <cstdint>

namespace Unity
{
    typedef enum Il2CppTypeEnum
    {
        IL2CPP_TYPE_END           = 0x00,
        IL2CPP_TYPE_VOID          = 0x01,
        IL2CPP_TYPE_BOOLEAN       = 0x02,
        IL2CPP_TYPE_CHAR          = 0x03,
        IL2CPP_TYPE_I1            = 0x04,
        IL2CPP_TYPE_U1            = 0x05,
        IL2CPP_TYPE_I2            = 0x06,
        IL2CPP_TYPE_U2            = 0x07,
        IL2CPP_TYPE_I4            = 0x08,
        IL2CPP_TYPE_U4            = 0x09,
        IL2CPP_TYPE_I8            = 0x0a,
        IL2CPP_TYPE_U8            = 0x0b,
        IL2CPP_TYPE_R4            = 0x0c,
        IL2CPP_TYPE_R8            = 0x0d,
        IL2CPP_TYPE_STRING        = 0x0e,
        IL2CPP_TYPE_PTR           = 0x0f,
        IL2CPP_TYPE_BYREF         = 0x10,
        IL2CPP_TYPE_VALUETYPE     = 0x11,
        IL2CPP_TYPE_CLASS         = 0x12,
        IL2CPP_TYPE_VAR           = 0x13,
        IL2CPP_TYPE_ARRAY         = 0x14,
        IL2CPP_TYPE_GENERICINST   = 0x15,
        IL2CPP_TYPE_TYPEDBYREF    = 0x16,
        IL2CPP_TYPE_I             = 0x18,
        IL2CPP_TYPE_U             = 0x19,
        IL2CPP_TYPE_FNPTR         = 0x1b,
        IL2CPP_TYPE_OBJECT        = 0x1c,
        IL2CPP_TYPE_SZARRAY       = 0x1d,
        IL2CPP_TYPE_MVAR          = 0x1e,
        IL2CPP_TYPE_CMOD_REQD     = 0x1f,
        IL2CPP_TYPE_CMOD_OPT      = 0x20,
        IL2CPP_TYPE_INTERNAL      = 0x21,
        IL2CPP_TYPE_MODIFIER      = 0x40,
        IL2CPP_TYPE_SENTINEL      = 0x41,
        IL2CPP_TYPE_PINNED        = 0x45,
        IL2CPP_TYPE_ENUM          = 0x55,
        IL2CPP_TYPE_IL2CPP_TYPE_INDEX = 0xff,
    } Il2CppTypeEnum;

    enum FieldAttribute : uint32_t
    {
        FIELD_ATTRIBUTE_FIELD_ACCESS_MASK   = 0x0007,
        FIELD_ATTRIBUTE_COMPILER_CONTROLLED = 0x0000,
        FIELD_ATTRIBUTE_PRIVATE             = 0x0001,
        FIELD_ATTRIBUTE_FAM_AND_ASSEM       = 0x0002,
        FIELD_ATTRIBUTE_ASSEMBLY            = 0x0003,
        FIELD_ATTRIBUTE_FAMILY              = 0x0004,
        FIELD_ATTRIBUTE_FAM_OR_ASSEM        = 0x0005,
        FIELD_ATTRIBUTE_PUBLIC              = 0x0006,
        FIELD_ATTRIBUTE_STATIC              = 0x0010,
        FIELD_ATTRIBUTE_INIT_ONLY           = 0x0020,
        FIELD_ATTRIBUTE_LITERAL             = 0x0040,
        FIELD_ATTRIBUTE_NOT_SERIALIZED      = 0x0080,
        FIELD_ATTRIBUTE_SPECIAL_NAME        = 0x0200,
        FIELD_ATTRIBUTE_PINVOKE_IMPL        = 0x2000,
        FIELD_ATTRIBUTE_RESERVED_MASK       = 0x9500,
        FIELD_ATTRIBUTE_RT_SPECIAL_NAME     = 0x0400,
        FIELD_ATTRIBUTE_HAS_FIELD_MARSHAL   = 0x1000,
        FIELD_ATTRIBUTE_HAS_DEFAULT         = 0x8000,
        FIELD_ATTRIBUTE_HAS_FIELD_RVA       = 0x0100,
    };

    enum MethodImplAttribute : uint32_t
    {
        METHOD_IMPL_ATTRIBUTE_CODE_TYPE_MASK      = 0x0003,
        METHOD_IMPL_ATTRIBUTE_IL                  = 0x0000,
        METHOD_IMPL_ATTRIBUTE_NATIVE              = 0x0001,
        METHOD_IMPL_ATTRIBUTE_OPTIL               = 0x0002,
        METHOD_IMPL_ATTRIBUTE_RUNTIME             = 0x0003,
        METHOD_IMPL_ATTRIBUTE_MANAGED_MASK        = 0x0004,
        METHOD_IMPL_ATTRIBUTE_UNMANAGED           = 0x0004,
        METHOD_IMPL_ATTRIBUTE_MANAGED             = 0x0000,
        METHOD_IMPL_ATTRIBUTE_FORWARD_REF         = 0x0010,
        METHOD_IMPL_ATTRIBUTE_PRESERVE_SIG        = 0x0080,
        METHOD_IMPL_ATTRIBUTE_INTERNAL_CALL       = 0x1000,
        METHOD_IMPL_ATTRIBUTE_SYNCHRONIZED        = 0x0020,
        METHOD_IMPL_ATTRIBUTE_NOINLINING          = 0x0008,
        METHOD_IMPL_ATTRIBUTE_MAX_METHOD_IMPL_VAL = 0xffff,
    };

    enum MethodAttribute : uint32_t
    {
        METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK    = 0x0007,
        METHOD_ATTRIBUTE_COMPILER_CONTROLLED   = 0x0000,
        METHOD_ATTRIBUTE_PRIVATE               = 0x0001,
        METHOD_ATTRIBUTE_FAM_AND_ASSEM         = 0x0002,
        METHOD_ATTRIBUTE_ASSEM                 = 0x0003,
        METHOD_ATTRIBUTE_FAMILY                = 0x0004,
        METHOD_ATTRIBUTE_FAM_OR_ASSEM          = 0x0005,
        METHOD_ATTRIBUTE_PUBLIC                = 0x0006,
        METHOD_ATTRIBUTE_STATIC                = 0x0010,
        METHOD_ATTRIBUTE_FINAL                 = 0x0020,
        METHOD_ATTRIBUTE_VIRTUAL               = 0x0040,
        METHOD_ATTRIBUTE_HIDE_BY_SIG           = 0x0080,
        METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK    = 0x0100,
        METHOD_ATTRIBUTE_REUSE_SLOT            = 0x0000,
        METHOD_ATTRIBUTE_NEW_SLOT              = 0x0100,
        METHOD_ATTRIBUTE_STRICT                = 0x0200,
        METHOD_ATTRIBUTE_ABSTRACT              = 0x0400,
        METHOD_ATTRIBUTE_SPECIAL_NAME          = 0x0800,
        METHOD_ATTRIBUTE_PINVOKE_IMPL          = 0x2000,
        METHOD_ATTRIBUTE_UNMANAGED_EXPORT      = 0x0008,
        METHOD_ATTRIBUTE_RESERVED_MASK         = 0xd000,
        METHOD_ATTRIBUTE_RT_SPECIAL_NAME       = 0x1000,
        METHOD_ATTRIBUTE_HAS_SECURITY          = 0x4000,
        METHOD_ATTRIBUTE_REQUIRE_SEC_OBJECT    = 0x8000,
    };

    enum TypeAttribute : uint32_t
    {
        TYPE_ATTRIBUTE_VISIBILITY_MASK      = 0x00000007,
        TYPE_ATTRIBUTE_NOT_PUBLIC           = 0x00000000,
        TYPE_ATTRIBUTE_PUBLIC               = 0x00000001,
        TYPE_ATTRIBUTE_NESTED_PUBLIC        = 0x00000002,
        TYPE_ATTRIBUTE_NESTED_PRIVATE       = 0x00000003,
        TYPE_ATTRIBUTE_NESTED_FAMILY        = 0x00000004,
        TYPE_ATTRIBUTE_NESTED_ASSEMBLY      = 0x00000005,
        TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM = 0x00000006,
        TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM  = 0x00000007,
        TYPE_ATTRIBUTE_LAYOUT_MASK          = 0x00000018,
        TYPE_ATTRIBUTE_AUTO_LAYOUT          = 0x00000000,
        TYPE_ATTRIBUTE_SEQUENTIAL_LAYOUT    = 0x00000008,
        TYPE_ATTRIBUTE_EXPLICIT_LAYOUT      = 0x00000010,
        TYPE_ATTRIBUTE_CLASS_SEMANTIC_MASK  = 0x00000020,
        TYPE_ATTRIBUTE_CLASS                = 0x00000000,
        TYPE_ATTRIBUTE_INTERFACE            = 0x00000020,
        TYPE_ATTRIBUTE_ABSTRACT             = 0x00000080,
        TYPE_ATTRIBUTE_SEALED               = 0x00000100,
        TYPE_ATTRIBUTE_SPECIAL_NAME         = 0x00000400,
        TYPE_ATTRIBUTE_IMPORT               = 0x00001000,
        TYPE_ATTRIBUTE_SERIALIZABLE         = 0x00002000,
        TYPE_ATTRIBUTE_STRING_FORMAT_MASK   = 0x00030000,
        TYPE_ATTRIBUTE_ANSI_CLASS           = 0x00000000,
        TYPE_ATTRIBUTE_UNICODE_CLASS        = 0x00010000,
        TYPE_ATTRIBUTE_AUTO_CLASS           = 0x00020000,
        TYPE_ATTRIBUTE_BEFORE_FIELD_INIT    = 0x00100000,
        TYPE_ATTRIBUTE_FORWARDER            = 0x00200000,
        TYPE_ATTRIBUTE_RESERVED_MASK        = 0x00040800,
        TYPE_ATTRIBUTE_RT_SPECIAL_NAME      = 0x00000800,
        TYPE_ATTRIBUTE_HAS_SECURITY         = 0x00040000,
    };

    enum ParamAttribute : uint32_t
    {
        PARAM_ATTRIBUTE_IN               = 0x0001,
        PARAM_ATTRIBUTE_OUT              = 0x0002,
        PARAM_ATTRIBUTE_OPTIONAL         = 0x0010,
        PARAM_ATTRIBUTE_RESERVED_MASK    = 0xf000,
        PARAM_ATTRIBUTE_HAS_DEFAULT      = 0x1000,
        PARAM_ATTRIBUTE_HAS_FIELD_MARSHAL= 0x2000,
        PARAM_ATTRIBUTE_UNUSED           = 0xcfe0,
    };

    enum GenericParameterAttribute : uint32_t
    {
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_NON_VARIANT                        = 0x00,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_COVARIANT                          = 0x01,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_CONTRAVARIANT                      = 0x02,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_VARIANCE_MASK                      = 0x03,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_REFERENCE_TYPE_CONSTRAINT          = 0x04,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_NOT_NULLABLE_VALUE_TYPE_CONSTRAINT = 0x08,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_DEFAULT_CONSTRUCTOR_CONSTRAINT     = 0x10,
        IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_SPECIAL_CONSTRAINT_MASK            = 0x1C,
    };

    enum AssemblyRefFlag : uint32_t
    {
        ASSEMBLYREF_FULL_PUBLIC_KEY_FLAG             = 0x00000001,
        ASSEMBLYREF_RETARGETABLE_FLAG                = 0x00000100,
        ASSEMBLYREF_ENABLEJITCOMPILE_TRACKING_FLAG   = 0x00008000,
        ASSEMBLYREF_DISABLEJITCOMPILE_OPTIMIZER_FLAG = 0x00004000,
    };

    struct il2cppType
    {
        union
        {
            void*        dummy;
            unsigned int classIndex;
            void*        typeHandle;
            il2cppType*  type;
            void*        array;
            unsigned int genericParameterIndex;
            void*        genericParameterHandle;
            void*        genericClass;
        } data;
        unsigned int attrs     : 16;
        Il2CppTypeEnum type    : 8;
        unsigned int num_mods  : 5;
        unsigned int byref     : 1;
        unsigned int pinned    : 1;
        unsigned int valuetype : 1;
    };

    struct il2cppArrayBounds
    {
        uintptr_t length;
        int       lowerBound;
    };

    struct il2cppAssemblyName
    {
        const char*    name;
        const char*    culture;
        const uint8_t* publicKey;
        uint32_t       hashAlg;
        int32_t        hashLen;
        uint32_t       flags;
        int32_t        major;
        int32_t        minor;
        int32_t        build;
        int32_t        revision;
        uint8_t        publicKeyToken[8];
    };

    struct il2cppImage
    {
        const char* name;
        const char* nameNoExt;
    };

    struct il2cppAssembly
    {
        il2cppImage* image;
    };

    struct il2cppObject
    {
        union
        {
            void* klass;
            void* vtable;
        };
        void* monitor;
    };

    struct il2cppFieldInfo
    {
        const char*  name;
        il2cppType*  type;
        void*        parent;
        int32_t      offset;
        uint32_t     token;
    };

    struct il2cppPropertyInfo
    {
        void*        parent;
        const char*  name;
        void*        get;
        void*        set;
        uint32_t     attrs;
        uint32_t     token;
    };

    struct il2cppMethodInfo
    {
        void* methodPointer;
    };

    struct il2cppClass
    {
        const il2cppImage* image;
        void*              gcDesc;
        const char*        name;
        const char*        namespaze;
    };
}