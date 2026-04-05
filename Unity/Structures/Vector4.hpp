#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Unity
{
    struct Vector4
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            float data[4];
        };

        inline Vector4();
        inline Vector4(float data[]);
        inline Vector4(float value);
        inline Vector4(float x, float y, float z, float w);

        static inline Vector4 Zero();
        static inline Vector4 One();

        static inline float   Dot(Vector4 lhs, Vector4 rhs);
        static inline float   Distance(Vector4 a, Vector4 b);
        static inline float   Magnitude(Vector4 v);
        static inline float   SqrMagnitude(Vector4 v);
        static inline Vector4 Normalized(Vector4 v);
        static inline Vector4 Lerp(Vector4 a, Vector4 b, float t);
        static inline Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
        static inline Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);
        static inline Vector4 Scale(Vector4 a, Vector4 b);
        static inline Vector4 Project(Vector4 a, Vector4 b);
        static inline Vector4 ClampMagnitude(Vector4 vector, float maxLength);
        static inline Vector4 Max(Vector4 a, Vector4 b);
        static inline Vector4 Min(Vector4 a, Vector4 b);

        inline struct Vector4& operator+=(const float rhs);
        inline struct Vector4& operator-=(const float rhs);
        inline struct Vector4& operator*=(const float rhs);
        inline struct Vector4& operator/=(const float rhs);
        inline struct Vector4& operator+=(const Vector4 rhs);
        inline struct Vector4& operator-=(const Vector4 rhs);
    };

    inline Vector4 operator-(Vector4 rhs);
    inline Vector4 operator+(Vector4 lhs, const float rhs);
    inline Vector4 operator-(Vector4 lhs, const float rhs);
    inline Vector4 operator*(Vector4 lhs, const float rhs);
    inline Vector4 operator/(Vector4 lhs, const float rhs);
    inline Vector4 operator+(const float lhs, Vector4 rhs);
    inline Vector4 operator-(const float lhs, Vector4 rhs);
    inline Vector4 operator*(const float lhs, Vector4 rhs);
    inline Vector4 operator/(const float lhs, Vector4 rhs);
    inline Vector4 operator+(Vector4 lhs, const Vector4 rhs);
    inline Vector4 operator-(Vector4 lhs, const Vector4 rhs);
    inline bool    operator==(const Vector4 lhs, const Vector4 rhs);
    inline bool    operator!=(const Vector4 lhs, const Vector4 rhs);


    Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4::Vector4(float data[]) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
    Vector4::Vector4(float value) : x(value), y(value), z(value), w(value) {}
    Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector4 Vector4::Zero() { return Vector4(0, 0, 0, 0); }
    Vector4 Vector4::One()  { return Vector4(1, 1, 1, 1); }

    float Vector4::Dot(Vector4 lhs, Vector4 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    float Vector4::SqrMagnitude(Vector4 v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    float Vector4::Magnitude(Vector4 v)
    {
        return sqrt(SqrMagnitude(v));
    }

    float Vector4::Distance(Vector4 a, Vector4 b)
    {
        return Magnitude(a - b);
    }

    Vector4 Vector4::Normalized(Vector4 v)
    {
        float mag = Magnitude(v);
        if (mag == 0)
            return Vector4::Zero();
        return v / mag;
    }

    Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return LerpUnclamped(a, b, t);
    }

    Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
    {
        return (b - a) * t + a;
    }

    Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
    {
        Vector4 d = target - current;
        float m = Magnitude(d);
        if (m < maxDistanceDelta || m == 0)
            return target;
        return current + (d * maxDistanceDelta / m);
    }

    Vector4 Vector4::Scale(Vector4 a, Vector4 b)
    {
        return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

    Vector4 Vector4::Project(Vector4 a, Vector4 b)
    {
        float m = Magnitude(b);
        return Dot(a, b) / (m * m) * b;
    }

    Vector4 Vector4::ClampMagnitude(Vector4 vector, float maxLength)
    {
        float length = Magnitude(vector);
        if (length > maxLength)
            vector *= maxLength / length;
        return vector;
    }

    Vector4 Vector4::Max(Vector4 a, Vector4 b)
    {
        float x = a.x > b.x ? a.x : b.x;
        float y = a.y > b.y ? a.y : b.y;
        float z = a.z > b.z ? a.z : b.z;
        float w = a.w > b.w ? a.w : b.w;
        return Vector4(x, y, z, w);
    }

    Vector4 Vector4::Min(Vector4 a, Vector4 b)
    {
        float x = a.x > b.x ? b.x : a.x;
        float y = a.y > b.y ? b.y : a.y;
        float z = a.z > b.z ? b.z : a.z;
        float w = a.w > b.w ? b.w : a.w;
        return Vector4(x, y, z, w);
    }

    struct Vector4& Vector4::operator+=(const float rhs) { x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
    struct Vector4& Vector4::operator-=(const float rhs) { x -= rhs; y -= rhs; z -= rhs; w -= rhs; return *this; }
    struct Vector4& Vector4::operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
    struct Vector4& Vector4::operator/=(const float rhs) { x /= rhs; y /= rhs; z /= rhs; w /= rhs; return *this; }

    struct Vector4& Vector4::operator+=(const Vector4 rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
    struct Vector4& Vector4::operator-=(const Vector4 rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }

    Vector4 operator-(Vector4 rhs)                      { return rhs * -1; }
    Vector4 operator+(Vector4 lhs, const float rhs)     { return lhs += rhs; }
    Vector4 operator-(Vector4 lhs, const float rhs)     { return lhs -= rhs; }
    Vector4 operator*(Vector4 lhs, const float rhs)     { return lhs *= rhs; }
    Vector4 operator/(Vector4 lhs, const float rhs)     { return lhs /= rhs; }
    Vector4 operator+(const float lhs, Vector4 rhs)     { return rhs += lhs; }
    Vector4 operator-(const float lhs, Vector4 rhs)     { return rhs -= lhs; }
    Vector4 operator*(const float lhs, Vector4 rhs)     { return rhs *= lhs; }
    Vector4 operator/(const float lhs, Vector4 rhs)     { return rhs /= lhs; }
    Vector4 operator+(Vector4 lhs, const Vector4 rhs)   { return lhs += rhs; }
    Vector4 operator-(Vector4 lhs, const Vector4 rhs)   { return lhs -= rhs; }

    bool operator==(const Vector4 lhs, const Vector4 rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    bool operator!=(const Vector4 lhs, const Vector4 rhs)
    {
        return !(lhs == rhs);
    }
}
