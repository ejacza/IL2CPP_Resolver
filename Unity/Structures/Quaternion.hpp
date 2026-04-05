#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define SMALL_float 0.0000000001

namespace Unity
{
    struct Quaternion
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

        inline Quaternion();
        inline Quaternion(float data[]);
        inline Quaternion(Vector3 vector, float scalar);
        inline Quaternion(float x, float y, float z, float w);

        static inline Quaternion Identity();

        static inline float      Angle(Quaternion a, Quaternion b);
        static inline Quaternion Conjugate(Quaternion rotation);
        static inline float      Dot(Quaternion lhs, Quaternion rhs);
        static inline Quaternion FromAngleAxis(float angle, Vector3 axis);
        static inline Quaternion FromEuler(Vector3 rotation);
        static inline Quaternion FromEuler(float x, float y, float z);
        static inline Quaternion FromToRotation(Vector3 fromVector, Vector3 toVector);
        static inline Quaternion Inverse(Quaternion rotation);
        static inline Quaternion Lerp(Quaternion a, Quaternion b, float t);
        static inline Quaternion LerpUnclamped(Quaternion a, Quaternion b, float t);
        static inline Quaternion LookRotation(Vector3 forward);
        static inline Quaternion LookRotation(Vector3 forward, Vector3 upwards);
        static inline float      Norm(Quaternion rotation);
        static inline Quaternion Normalized(Quaternion rotation);
        static inline Quaternion RotateTowards(Quaternion from, Quaternion to, float maxRadiansDelta);
        static inline Quaternion Slerp(Quaternion a, Quaternion b, float t);
        static inline Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t);
        static inline void       ToAngleAxis(Quaternion rotation, float &angle, Vector3 &axis);
        static inline Vector3    ToEuler(Quaternion rotation);

        inline struct Quaternion& operator+=(const float rhs);
        inline struct Quaternion& operator-=(const float rhs);
        inline struct Quaternion& operator*=(const float rhs);
        inline struct Quaternion& operator/=(const float rhs);
        inline struct Quaternion& operator+=(const Quaternion rhs);
        inline struct Quaternion& operator-=(const Quaternion rhs);
        inline struct Quaternion& operator*=(const Quaternion rhs);
    };

    inline Quaternion operator-(Quaternion rhs);
    inline Quaternion operator+(Quaternion lhs, const float rhs);
    inline Quaternion operator-(Quaternion lhs, const float rhs);
    inline Quaternion operator*(Quaternion lhs, const float rhs);
    inline Quaternion operator/(Quaternion lhs, const float rhs);
    inline Quaternion operator+(const float lhs, Quaternion rhs);
    inline Quaternion operator-(const float lhs, Quaternion rhs);
    inline Quaternion operator*(const float lhs, Quaternion rhs);
    inline Quaternion operator/(const float lhs, Quaternion rhs);
    inline Quaternion operator+(Quaternion lhs, const Quaternion rhs);
    inline Quaternion operator-(Quaternion lhs, const Quaternion rhs);
    inline Quaternion operator*(Quaternion lhs, const Quaternion rhs);
    inline Vector3    operator*(Quaternion lhs, const Vector3 rhs);
    inline bool       operator==(const Quaternion lhs, const Quaternion rhs);
    inline bool       operator!=(const Quaternion lhs, const Quaternion rhs);


    Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
    Quaternion::Quaternion(float data[]) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
    Quaternion::Quaternion(Vector3 vector, float scalar) : x(vector.x), y(vector.y), z(vector.z), w(scalar) {}
    Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Quaternion Quaternion::Identity() { return Quaternion(0, 0, 0, 1); }

    float Quaternion::Angle(Quaternion a, Quaternion b)
    {
        float dot = Dot(a, b);
        return acos(fmin(fabs(dot), 1)) * 2;
    }

    Quaternion Quaternion::Conjugate(Quaternion rotation)
    {
        return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
    }

    float Quaternion::Dot(Quaternion lhs, Quaternion rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    Quaternion Quaternion::FromAngleAxis(float angle, Vector3 axis)
    {
        Quaternion q;
        float m = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
        float s = sin(angle / 2) / m;
        q.x = axis.x * s;
        q.y = axis.y * s;
        q.z = axis.z * s;
        q.w = cos(angle / 2);
        return q;
    }

    Quaternion Quaternion::FromEuler(Vector3 rotation)
    {
        return FromEuler(rotation.x, rotation.y, rotation.z);
    }

    Quaternion Quaternion::FromEuler(float x, float y, float z)
    {
        float cx = cos(x * 0.5);
        float cy = cos(y * 0.5);
        float cz = cos(z * 0.5);
        float sx = sin(x * 0.5);
        float sy = sin(y * 0.5);
        float sz = sin(z * 0.5);
        Quaternion q;
        q.x = cx * sy * sz + cy * cz * sx;
        q.y = cx * cz * sy - cy * sx * sz;
        q.z = cx * cy * sz - cz * sx * sy;
        q.w = sx * sy * sz + cx * cy * cz;
        return q;
    }

    Quaternion Quaternion::FromToRotation(Vector3 fromVector, Vector3 toVector)
    {
        float dot = Vector3::Dot(fromVector, toVector);
        float k = sqrt(Vector3::SqrMagnitude(fromVector) * Vector3::SqrMagnitude(toVector));
        if (fabs(dot / k + 1) < 0.00001)
        {
            Vector3 ortho = Vector3::Orthogonal(fromVector);
            return Quaternion(Vector3::Normalized(ortho), 0);
        }
        Vector3 cross = Vector3::Cross(fromVector, toVector);
        return Normalized(Quaternion(cross, dot + k));
    }

    Quaternion Quaternion::Inverse(Quaternion rotation)
    {
        float n = Norm(rotation);
        return Conjugate(rotation) / (n * n);
    }

    Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
    {
        if (t < 0) return Normalized(a);
        else if (t > 1) return Normalized(b);
        return LerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        Quaternion quaternion;
        if (Dot(a, b) >= 0)
            quaternion = a * (1 - t) + b * t;
        else
            quaternion = a * (1 - t) - b * t;
        return Normalized(quaternion);
    }

    Quaternion Quaternion::LookRotation(Vector3 forward)
    {
        return LookRotation(forward, Vector3(0, 1, 0));
    }

    Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
    {
        forward  = Vector3::Normalized(forward);
        upwards  = Vector3::Normalized(upwards);

        if (Vector3::SqrMagnitude(forward) < SMALL_float || Vector3::SqrMagnitude(upwards) < SMALL_float)
            return Quaternion::Identity();

        if (1 - fabs(Vector3::Dot(forward, upwards)) < SMALL_float)
            return FromToRotation(Vector3::Forward(), forward);

        Vector3 right = Vector3::Normalized(Vector3::Cross(upwards, forward));
        upwards = Vector3::Cross(forward, right);

        Quaternion quaternion;
        float radicand = right.x + upwards.y + forward.z;

        if (radicand > 0)
        {
            quaternion.w = sqrt(1.0 + radicand) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.w);
            quaternion.x = (upwards.z - forward.y) * recip;
            quaternion.y = (forward.x - right.z)   * recip;
            quaternion.z = (right.y   - upwards.x)  * recip;
        }
        else if (right.x >= upwards.y && right.x >= forward.z)
        {
            quaternion.x = sqrt(1.0 + right.x - upwards.y - forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.x);
            quaternion.w = (upwards.z - forward.y) * recip;
            quaternion.z = (forward.x + right.z)   * recip;
            quaternion.y = (right.y   + upwards.x)  * recip;
        }
        else if (upwards.y > forward.z)
        {
            quaternion.y = sqrt(1.0 - right.x + upwards.y - forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.y);
            quaternion.z = (upwards.z + forward.y) * recip;
            quaternion.w = (forward.x - right.z)   * recip;
            quaternion.x = (right.y   + upwards.x)  * recip;
        }
        else
        {
            quaternion.z = sqrt(1.0 - right.x - upwards.y + forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.z);
            quaternion.y = (upwards.z + forward.y) * recip;
            quaternion.x = (forward.x + right.z)   * recip;
            quaternion.w = (right.y   - upwards.x)  * recip;
        }

        return quaternion;
    }

    float Quaternion::Norm(Quaternion rotation)
    {
        return sqrt(
            rotation.x * rotation.x +
            rotation.y * rotation.y +
            rotation.z * rotation.z +
            rotation.w * rotation.w
        );
    }

    Quaternion Quaternion::Normalized(Quaternion rotation)
    {
        return rotation / Norm(rotation);
    }

    Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to, float maxRadiansDelta)
    {
        float angle = Quaternion::Angle(from, to);
        if (angle == 0)
            return to;
        maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
        float t = fmin(1, maxRadiansDelta / angle);
        return Quaternion::SlerpUnclamped(from, to, t);
    }

    Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
    {
        if (t < 0) return Normalized(a);
        else if (t > 1) return Normalized(b);
        return SlerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        float n1;
        float n2;
        float n3   = Dot(a, b);
        bool  flag = false;

        if (n3 < 0)
        {
            flag = true;
            n3   = -n3;
        }

        if (n3 > 0.999999)
        {
            n2 = 1 - t;
            n1 = flag ? -t : t;
        }
        else
        {
            float n4 = acos(n3);
            float n5 = 1 / sin(n4);
            n2 = sin((1 - t) * n4) * n5;
            n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
        }

        Quaternion quaternion;
        quaternion.x = (n2 * a.x) + (n1 * b.x);
        quaternion.y = (n2 * a.y) + (n1 * b.y);
        quaternion.z = (n2 * a.z) + (n1 * b.z);
        quaternion.w = (n2 * a.w) + (n1 * b.w);
        return Normalized(quaternion);
    }

    void Quaternion::ToAngleAxis(Quaternion rotation, float &angle, Vector3 &axis)
    {
        if (rotation.w > 1)
            rotation = Normalized(rotation);

        angle     = 2 * acos(rotation.w);
        float s   = sqrt(1 - rotation.w * rotation.w);

        if (s < 0.00001)
        {
            axis.x = 1;
            axis.y = 0;
            axis.z = 0;
        }
        else
        {
            axis.x = rotation.x / s;
            axis.y = rotation.y / s;
            axis.z = rotation.z / s;
        }
    }

    Vector3 Quaternion::ToEuler(Quaternion rotation)
    {
        float sqw  = rotation.w * rotation.w;
        float sqx  = rotation.x * rotation.x;
        float sqy  = rotation.y * rotation.y;
        float sqz  = rotation.z * rotation.z;
        float unit = sqx + sqy + sqz + sqw;
        float test = rotation.x * rotation.w - rotation.y * rotation.z;
        Vector3 v;

        if (test > 0.4995f * unit)
        {
            v.y = 2 * atan2(rotation.y, rotation.x);
            v.x = M_PI_2;
            v.z = 0;
            return v;
        }

        if (test < -0.4995f * unit)
        {
            v.y = -2 * atan2(rotation.y, rotation.x);
            v.x = -M_PI_2;
            v.z = 0;
            return v;
        }

        v.y = atan2(2 * rotation.w * rotation.y + 2 * rotation.z * rotation.x,
                    1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
        v.x = asin(2 * (rotation.w * rotation.x - rotation.y * rotation.z));
        v.z = atan2(2 * rotation.w * rotation.z + 2 * rotation.x * rotation.y,
                    1 - 2 * (rotation.z * rotation.z + rotation.x * rotation.x));
        return v;
    }

    struct Quaternion& Quaternion::operator+=(const float rhs) { x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
    struct Quaternion& Quaternion::operator-=(const float rhs) { x -= rhs; y -= rhs; z -= rhs; w -= rhs; return *this; }
    struct Quaternion& Quaternion::operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
    struct Quaternion& Quaternion::operator/=(const float rhs) { x /= rhs; y /= rhs; z /= rhs; w /= rhs; return *this; }

    struct Quaternion& Quaternion::operator+=(const Quaternion rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
    struct Quaternion& Quaternion::operator-=(const Quaternion rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }

    struct Quaternion& Quaternion::operator*=(const Quaternion rhs)
    {
        Quaternion q;
        q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
        q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
        q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
        q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
        *this = q;
        return *this;
    }

    Quaternion operator-(Quaternion rhs)                          { return rhs * -1; }
    Quaternion operator+(Quaternion lhs, const float rhs)         { return lhs += rhs; }
    Quaternion operator-(Quaternion lhs, const float rhs)         { return lhs -= rhs; }
    Quaternion operator*(Quaternion lhs, const float rhs)         { return lhs *= rhs; }
    Quaternion operator/(Quaternion lhs, const float rhs)         { return lhs /= rhs; }
    Quaternion operator+(const float lhs, Quaternion rhs)         { return rhs += lhs; }
    Quaternion operator-(const float lhs, Quaternion rhs)         { return rhs -= lhs; }
    Quaternion operator*(const float lhs, Quaternion rhs)         { return rhs *= lhs; }
    Quaternion operator/(const float lhs, Quaternion rhs)         { return rhs /= lhs; }
    Quaternion operator+(Quaternion lhs, const Quaternion rhs)    { return lhs += rhs; }
    Quaternion operator-(Quaternion lhs, const Quaternion rhs)    { return lhs -= rhs; }
    Quaternion operator*(Quaternion lhs, const Quaternion rhs)    { return lhs *= rhs; }

    Vector3 operator*(Quaternion lhs, const Vector3 rhs)
    {
        Vector3 u = Vector3(lhs.x, lhs.y, lhs.z);
        float   s = lhs.w;
        return u * (Vector3::Dot(u, rhs) * 2)
               + rhs * (s * s - Vector3::Dot(u, u))
               + Vector3::Cross(u, rhs) * (2.0 * s);
    }

    bool operator==(const Quaternion lhs, const Quaternion rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    bool operator!=(const Quaternion lhs, const Quaternion rhs)
    {
        return !(lhs == rhs);
    }
}
