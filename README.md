# IL2CPP Resolver

IL2CPP resolver for Android, providing runtime access to IL2CPP functions and Unity API wrappers.

## Usage

```cpp
#include "IL2CPP_Resolver.hpp"

int main()
{
    IL2CPP::Initialize(true);
    return 0;
}
```

## Quick Examples

### Find a Class

```cpp
Unity::il2cppClass* pClass = IL2CPP::Class::Find("UnityEngine.GameObject");
```

### Get Method Pointer

```cpp
// By class pointer
void* pMethod = IL2CPP::Class::Utils::GetMethodPointer(pClass, "get_transform", 0);

// By class name string
void* pMethod = IL2CPP::Class::Utils::GetMethodPointer("UnityEngine.GameObject", "Find", 1);

// With parameter types (for overloaded methods)
void* pMethod = IL2CPP::Class::Utils::GetMethodPointer("MyNamespace.Player", "TakeDamage", { "Int32", "Boolean" });
```

### Call Static Method

```cpp
// Via Class::Utils — one-liner: find class, get method, call it
float deltaTime = IL2CPP::Class::Utils::CallMethod<float>("UnityEngine.Time", "get_deltaTime");

// With arguments
int result = IL2CPP::Class::Utils::CallMethod<int>("MyNamespace.MathHelper", "Add", 5, 10);

// Via CClass static — same thing, different entry point
int result = IL2CPP::CClass::CallMethod<int>("MyNamespace.MathHelper", "Add", 5, 10);
```

### Call Instance Method

```cpp
// Get instance via FindObjectOfType
auto* camera = Unity::Object::FindObjectOfType<Unity::CCamera>("UnityEngine.Camera");

// Or via FindObjectsOfType (returns array)
auto* objects = Unity::Object::FindObjectsOfType<Unity::CGameObject>("UnityEngine.GameObject");

// Or via GameObject::Find
auto* obj = Unity::GameObject::Find("Player");

// Call instance methods
Vector3 pos = camera->CallMethod<Vector3>("get_position");
camera->CallMethod<void>("set_position", newPos);

// Access transform and call methods on it
auto* transform = obj->GetTransform();
transform->CallMethod<Vector3>("get_localPosition");
```

### Direct Function Pointer

```cpp
void* pMethod = IL2CPP::Class::Utils::GetMethodPointer("UnityEngine.Time", "get_deltaTime", 0);
if (pMethod) {
    float dt = reinterpret_cast<float(IL2CPP_CALLING_CONVENTION)()>(pMethod)();
}
```

### Resolve Internal Call

```cpp
void* pFunc = IL2CPP::ResolveCall("UnityEngine.Time::get_deltaTime");
if (pFunc) {
    float dt = reinterpret_cast<float(IL2CPP_CALLING_CONVENTION)()>(pFunc)();
}
```

## Structure

- `API/` — Core IL2CPP API wrappers (Class, Domain, String, Thread, ResolveCall)
- `Unity/` — Unity engine API wrappers and structures
- `Utils/` — Helper utilities (Hash, VTable, Helper)
- `xdl/` — Dynamic linker library for symbol resolution

## Notes

Some functions may still cause crashes

## Credits

- [sneakyevil/IL2CPP_Resolver](https://github.com/sneakyevil/IL2CPP_Resolver)
- [hexhacking/xDL](https://github.com/hexhacking/xDL)
