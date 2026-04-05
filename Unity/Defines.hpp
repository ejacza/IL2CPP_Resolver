#pragma once

// Calling Convention
#define UNITY_CALLING_CONVENTION *


// Application
#define UNITY_APPLICATION_CLASS                                     "UnityEngine.Application"
#define UNITY_APPLICATION_OPENURL                                   IL2CPP_RStr(UNITY_APPLICATION_CLASS"::OpenURL")
#define UNITY_APPLICATION_QUIT                                      IL2CPP_RStr(UNITY_APPLICATION_CLASS"::Quit")
#define UNITY_APPLICATION_GETPERSISTENTDATAPATH                     IL2CPP_RStr(UNITY_APPLICATION_CLASS"::get_persistentDataPath")
#define UNITY_APPLICATION_GETUNITYVERSION                           IL2CPP_RStr(UNITY_APPLICATION_CLASS"::get_unityVersion")
#define UNITY_APPLICATION_GETVERSION                                IL2CPP_RStr(UNITY_APPLICATION_CLASS"::get_version")
#define UNITY_APPLICATION_GETPRODUCTNAME                            IL2CPP_RStr(UNITY_APPLICATION_CLASS"::get_productName")

// Physics
#define UNITY_PHYSICS_CLASS                                         "UnityEngine.Physics"
#define UNITY_PHYSICS_GETGRAVITY                                    IL2CPP_RStr(UNITY_PHYSICS_CLASS"::get_gravity_Injected")
#define UNITY_PHYSICS_IGNORECOLLISION                               IL2CPP_RStr(UNITY_PHYSICS_CLASS"::IgnoreCollision(UnityEngine.Collider,UnityEngine.Collider,System.Boolean)")
#define UNITY_PHYSICS_RAYCAST                                       IL2CPP_RStr(UNITY_PHYSICS_CLASS"::Raycast(UnityEngine.Vector3,UnityEngine.Vector3,UnityEngine.RaycastHit&,System.Single,System.Int32,UnityEngine.QueryTriggerInteraction)")
#define UNITY_PHYSICS_RAYCAST_SIMPLE                                IL2CPP_RStr(UNITY_PHYSICS_CLASS"::Raycast(UnityEngine.Vector3,UnityEngine.Vector3,System.Single,System.Int32)")
#define UNITY_PHYSICS_RAYCASTALL                                    IL2CPP_RStr(UNITY_PHYSICS_CLASS"::RaycastAll(UnityEngine.Vector3,UnityEngine.Vector3,System.Single,System.Int32)")
#define UNITY_PHYSICS_RAYCASTNONALLOC                               IL2CPP_RStr(UNITY_PHYSICS_CLASS"::RaycastNonAlloc(UnityEngine.Vector3,UnityEngine.Vector3,UnityEngine.RaycastHit[],System.Single,System.Int32)")
#define UNITY_PHYSICS_SPHERECAST                                    IL2CPP_RStr(UNITY_PHYSICS_CLASS"::SphereCast(UnityEngine.Vector3,System.Single,UnityEngine.Vector3,UnityEngine.RaycastHit&,System.Single,System.Int32,UnityEngine.QueryTriggerInteraction)")
#define UNITY_PHYSICS_SPHERECASTNONALLOC                            IL2CPP_RStr(UNITY_PHYSICS_CLASS"::SphereCastNonAlloc(UnityEngine.Vector3,System.Single,UnityEngine.Vector3,UnityEngine.RaycastHit[],System.Single,System.Int32)")
#define UNITY_PHYSICS_OVERLAPSPHERE                                 IL2CPP_RStr(UNITY_PHYSICS_CLASS"::OverlapSphere(UnityEngine.Vector3,System.Single,System.Int32)")
#define UNITY_PHYSICS_OVERLAPSPHERENONALLOC                         IL2CPP_RStr(UNITY_PHYSICS_CLASS"::OverlapSphereNonAlloc(UnityEngine.Vector3,System.Single,UnityEngine.Collider[],System.Int32)")
#define UNITY_PHYSICS_COMPUTEPENETRATION                            IL2CPP_RStr(UNITY_PHYSICS_CLASS"::ComputePenetration")

// Camera
#define UNITY_CAMERA_CLASS                                          "UnityEngine.Camera"
#define UNITY_CAMERA_GETCURRENT                                     IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_current")
#define UNITY_CAMERA_GETMAIN                                        IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_main")
#define UNITY_CAMERA_GETDEPTH                                       IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_depth")
#define UNITY_CAMERA_SETDEPTH                                       IL2CPP_RStr(UNITY_CAMERA_CLASS"::set_depth")
#define UNITY_CAMERA_GETFIELDOFVIEW                                 IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_fieldOfView")
#define UNITY_CAMERA_SETFIELDOFVIEW                                 IL2CPP_RStr(UNITY_CAMERA_CLASS"::set_fieldOfView")
#define UNITY_CAMERA_WORLDTOSCREEN                                  IL2CPP_RStr(UNITY_CAMERA_CLASS"::WorldToScreenPoint_Injected")

// Component
#define UNITY_COMPONENT_CLASS                                        "UnityEngine.Component"
#define UNITY_COMPONENT_GETGAMEOBJECT                                IL2CPP_RStr(UNITY_COMPONENT_CLASS"::get_gameObject")
#define UNITY_COMPONENT_GETTRANSFORM                                IL2CPP_RStr(UNITY_COMPONENT_CLASS"::get_transform")
#define UNITY_COMPONENT_GETCOMPONENT                                IL2CPP_RStr(UNITY_COMPONENT_CLASS"::GetComponent")
#define UNITY_COMPONENT_TRYGETCOMPONENT                             IL2CPP_RStr(UNITY_COMPONENT_CLASS"::TryGetComponent")
#define UNITY_COMPONENT_GETCOMPONENTINCHILDREN                      IL2CPP_RStr(UNITY_COMPONENT_CLASS"::GetComponentInChildren")
#define UNITY_COMPONENT_GETCOMPONENTSINCHILDREN                     IL2CPP_RStr(UNITY_COMPONENT_CLASS"::GetComponentsInChildren")
#define UNITY_COMPONENT_GETCOMPONENTINPARENT                        IL2CPP_RStr(UNITY_COMPONENT_CLASS"::GetComponentInParent")
#define UNITY_COMPONENT_GETCOMPONENTS                               IL2CPP_RStr(UNITY_COMPONENT_CLASS"::GetComponents")
#define UNITY_COMPONENT_GETTAG                                      IL2CPP_RStr(UNITY_COMPONENT_CLASS"::get_tag")

// GameObject
#define UNITY_GAMEOBJECT_CLASS                                        "UnityEngine.GameObject"
#define UNITY_GAMEOBJECT_ADDCOMPONENT                                IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::Internal_AddComponentWithType")
#define UNITY_GAMEOBJECT_CREATEPRIMITIVE                             IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::CreatePrimitive")
#define UNITY_GAMEOBJECT_FIND                                        IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::Find")
#define UNITY_GAMEOBJECT_GETCOMPONENT                                IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentByName")
#define UNITY_GAMEOBJECT_GETCOMPONENTS                               IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentsInternal")
#define UNITY_GAMEOBJECT_GETCOMPONENTINCHILDREN                      IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentInChildren")
#define UNITY_GAMEOBJECT_GETACTIVE                                   IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_active")
#define UNITY_GAMEOBJECT_GETLAYER                                    IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_layer")
#define UNITY_GAMEOBJECT_GETTRANSFORM                                IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_transform")
#define UNITY_GAMEOBJECT_SETACTIVE                                   IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::set_active")
#define UNITY_GAMEOBJECT_SETLAYER                                    IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::set_layer")
#define UNITY_GAMEOBJECT_FINDGAMEOBJECTWITHTAG                       IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::FindGameObjectsWithTag")

// LayerMask
#define UNITY_LAYERMASK_CLASS                                        "UnityEngine.LayerMask"
#define UNITY_LAYERMASK_LAYERTONAME                                 IL2CPP_RStr(UNITY_LAYERMASK_CLASS"::LayerToName")
#define UNITY_LAYERMASK_NAMETOLAYER                                 IL2CPP_RStr(UNITY_LAYERMASK_CLASS"::NameToLayer")

// MonoBehaviour
#define UNITY_MONOBEHAVIOUR_CLASS                                   "UnityEngine.MonoBehaviour"

// Object
#define UNITY_OBJECT_CLASS                                            "UnityEngine.Object"
#define UNITY_OBJECT_DESTROY                                        IL2CPP_RStr(UNITY_OBJECT_CLASS"::Destroy")
#define UNITY_OBJECT_FINDOBJECTSOFTYPE                              IL2CPP_RStr(UNITY_OBJECT_CLASS"::FindObjectsOfType(System.Type,System.Boolean)")
#define UNITY_OBJECT_GETNAME                                        IL2CPP_RStr(UNITY_OBJECT_CLASS"::GetName")

// Rigidbody
#define UNITY_RIGIDBODY_CLASS                                        "UnityEngine.Rigidbody"
#define UNITY_RIGIDBODY_GETDETECTCOLLISIONS                         IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::get_detectCollisions")
#define UNITY_RIGIDBODY_GETVELOCITY                                 IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::get_velocity_Injected")
#define UNITY_RIGIDBODY_SETDETECTCOLLISIONS                         IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::set_detectCollisions")
#define UNITY_RIGIDBODY_SETVELOCITY                                 IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::set_velocity_Injected")

// Time
#define UNITY_TIME_CLASS                                            "UnityEngine.Time"
#define UNITY_TIME_GETFIXEDDELTAIME                                 IL2CPP_RStr(UNITY_TIME_CLASS"::get_fixedDeltaTime")
#define UNITY_TIME_GETTIMESCALE                                     IL2CPP_RStr(UNITY_TIME_CLASS"::get_timeScale")
#define UNITY_TIME_SETTIMESCALE                                     IL2CPP_RStr(UNITY_TIME_CLASS"::set_timeScale")
#define UNITY_TIME_GETDELTAIME                                      IL2CPP_RStr(UNITY_TIME_CLASS"::get_deltaTime")
#define UNITY_TIME_GETTIME                                          IL2CPP_RStr(UNITY_TIME_CLASS"::get_time")

// Screen
#define UNITY_SCREEN_CLASS                                          "UnityEngine.Screen"
#define UNITY_SCREEN_GETWIDTH                                       IL2CPP_RStr(UNITY_SCREEN_CLASS"::get_width")
#define UNITY_SCREEN_GETHEIGHT                                      IL2CPP_RStr(UNITY_SCREEN_CLASS"::get_height")
#define UNITY_SCREEN_GETDPI                                         IL2CPP_RStr(UNITY_SCREEN_CLASS"::get_dpi")


// Transform
#define UNITY_TRANSFORM_CLASS                                        "UnityEngine.Transform"
#define UNITY_TRANSFORM_GETPARENT                                   IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetParent")
#define UNITY_TRANSFORM_GETROOT                                     IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetRoot")
#define UNITY_TRANSFORM_GETCHILD                                    IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetChild")
#define UNITY_TRANSFORM_GETCHILDCOUNT                               IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_childCount")
#define UNITY_TRANSFORM_FINDCHILD                                   IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::FindRelativeTransformWithPath")
#define UNITY_TRANSFORM_GETPOSITION                                 IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_position_Injected")
#define UNITY_TRANSFORM_GETROTATION                                 IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_rotation_Injected")
#define UNITY_TRANSFORM_GETLOCALPOSITION                            IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_localPosition_Injected")
#define UNITY_TRANSFORM_GETLOCALSCALE                               IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_localScale_Injected")
#define UNITY_TRANSFORM_SETPOSITION                                 IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_position_Injected")
#define UNITY_TRANSFORM_SETROTATION                                 IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_rotation_Injected")
#define UNITY_TRANSFORM_GETFORWARD                                  IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_forward")
#define UNITY_TRANSFORM_SETFORWARD                                  IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_forward")
#define UNITY_TRANSFORM_SETLOCALPOSITION                            IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_localPosition_Injected")
#define UNITY_TRANSFORM_SETLOCALSCALE                               IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_localScale_Injected")

// Shader
#define UNITY_SHADER_CLASS                                          "UnityEngine.Shader"
#define UNITY_SHADER_FIND                                           IL2CPP_RStr(UNITY_SHADER_CLASS"::Find")
#define UNITY_SHADER_PROPERTYTOID                                   IL2CPP_RStr(UNITY_SHADER_CLASS"::PropertyToID")
#define UNITY_SHADER_ENABLEKEYWORD                                  IL2CPP_RStr(UNITY_SHADER_CLASS"::EnableKeyword")
#define UNITY_SHADER_DISABLEKEYWORD                                 IL2CPP_RStr(UNITY_SHADER_CLASS"::DisableKeyword")
#define UNITY_SHADER_SETGLOBALFLOAT                                 IL2CPP_RStr(UNITY_SHADER_CLASS"::SetGlobalFloat")

// Material
#define UNITY_MATERIAL_CLASS                                        "UnityEngine.Material"
#define UNITY_MATERIAL_CTOR                                         IL2CPP_RStr(UNITY_MATERIAL_CLASS"::.ctor")
#define UNITY_MATERIAL_GETSHADER                                    IL2CPP_RStr(UNITY_MATERIAL_CLASS"::get_shader")
#define UNITY_MATERIAL_SETSHADER                                    IL2CPP_RStr(UNITY_MATERIAL_CLASS"::set_shader")
#define UNITY_MATERIAL_GETCOLOR                                     IL2CPP_RStr(UNITY_MATERIAL_CLASS"::get_color")
#define UNITY_MATERIAL_SETCOLOR                                     IL2CPP_RStr(UNITY_MATERIAL_CLASS"::set_color")
#define UNITY_MATERIAL_SETCOLOR_BYID                                IL2CPP_RStr(UNITY_MATERIAL_CLASS"::SetColor")
#define UNITY_MATERIAL_SETRENDERQUEUE                               IL2CPP_RStr(UNITY_MATERIAL_CLASS"::set_renderQueue")
#define UNITY_MATERIAL_ENABLEKEYWORD                                IL2CPP_RStr(UNITY_MATERIAL_CLASS"::EnableKeyword")
#define UNITY_MATERIAL_DISABLEKEYWORD                               IL2CPP_RStr(UNITY_MATERIAL_CLASS"::DisableKeyword")
#define UNITY_MATERIAL_SETFLOAT                                     IL2CPP_RStr(UNITY_MATERIAL_CLASS"::SetFloat")
#define UNITY_MATERIAL_SETFLOAT_BYID                                IL2CPP_RStr(UNITY_MATERIAL_CLASS"::SetFloatImpl")
#define UNITY_MATERIAL_COPYPROPERTIES                               IL2CPP_RStr(UNITY_MATERIAL_CLASS"::CopyPropertiesFromMaterial")

// Renderer
#define UNITY_RENDERER_CLASS                                        "UnityEngine.Renderer"
#define UNITY_RENDERER_GETMATERIALS                                 IL2CPP_RStr(UNITY_RENDERER_CLASS"::get_materials")
#define UNITY_RENDERER_SETMATERIALS                                 IL2CPP_RStr(UNITY_RENDERER_CLASS"::set_materials")
#define UNITY_RENDERER_GETMATERIAL                                  IL2CPP_RStr(UNITY_RENDERER_CLASS"::get_material")
#define UNITY_RENDERER_SETMATERIAL                                  IL2CPP_RStr(UNITY_RENDERER_CLASS"::set_material")
#define UNITY_RENDERER_GETSHAREDMATERIALS                           IL2CPP_RStr(UNITY_RENDERER_CLASS"::get_sharedMaterials")
#define UNITY_RENDERER_SETSHAREDMATERIALS                           IL2CPP_RStr(UNITY_RENDERER_CLASS"::set_sharedMaterials")
#define UNITY_RENDERER_GETENABLED                                   IL2CPP_RStr(UNITY_RENDERER_CLASS"::get_enabled")
#define UNITY_RENDERER_SETENABLED                                   IL2CPP_RStr(UNITY_RENDERER_CLASS"::set_enabled")