#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Quaternion.hpp"

namespace Unity
{
    struct Matrix4x4
    {
        union
        {
            struct
            {
                float m00, m01, m02, m03;
                float m10, m11, m12, m13;
                float m20, m21, m22, m23;
                float m30, m31, m32, m33;
            };
            float m[4][4];
            float data[16];
        };

        inline Matrix4x4();
        inline Matrix4x4(float data[]);
        inline Matrix4x4(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

        static inline Matrix4x4 Zero();
        static inline Matrix4x4 Identity();

        static inline Matrix4x4 Translate(Vector3 v);
        static inline Matrix4x4 Scale(Vector3 scale);
        static inline Matrix4x4 RotateX(float rad);
        static inline Matrix4x4 RotateY(float rad);
        static inline Matrix4x4 RotateZ(float rad);
        static inline Matrix4x4 Rotate(Quaternion q);
        static inline Matrix4x4 TRS(Vector3 pos, Quaternion rot, Vector3 scale);

        static inline Matrix4x4 Perspective(float fovY, float aspect, float near, float far);
        static inline Matrix4x4 Ortho(float left, float right, float bottom, float top, float near, float far);
        static inline Matrix4x4 LookAt(Vector3 eye, Vector3 center, Vector3 up);

        static inline Matrix4x4 Transpose(Matrix4x4 mat);
        static inline float     Determinant(Matrix4x4 mat);
        static inline Matrix4x4 Inverse(Matrix4x4 mat);

        static inline Vector4   MultiplyVector4(Matrix4x4 mat, Vector4 v);
        static inline Vector3   MultiplyPoint(Matrix4x4 mat, Vector3 v);
        static inline Vector3   MultiplyVector(Matrix4x4 mat, Vector3 v);

        inline float& operator()(int row, int col);
        inline float  operator()(int row, int col) const;

        inline struct Matrix4x4& operator+=(const Matrix4x4 rhs);
        inline struct Matrix4x4& operator-=(const Matrix4x4 rhs);
        inline struct Matrix4x4& operator*=(const float rhs);
        inline struct Matrix4x4& operator/=(const float rhs);
    };

    inline Matrix4x4 operator+(Matrix4x4 lhs, const Matrix4x4 rhs);
    inline Matrix4x4 operator-(Matrix4x4 lhs, const Matrix4x4 rhs);
    inline Matrix4x4 operator*(Matrix4x4 lhs, const float rhs);
    inline Matrix4x4 operator*(const float lhs, Matrix4x4 rhs);
    inline Matrix4x4 operator/(Matrix4x4 lhs, const float rhs);
    inline Matrix4x4 operator*(Matrix4x4 lhs, const Matrix4x4 rhs);
    inline Vector4   operator*(Matrix4x4 lhs, const Vector4 rhs);
    inline bool      operator==(const Matrix4x4 lhs, const Matrix4x4 rhs);
    inline bool      operator!=(const Matrix4x4 lhs, const Matrix4x4 rhs);


    Matrix4x4::Matrix4x4()
        : m00(0), m01(0), m02(0), m03(0),
          m10(0), m11(0), m12(0), m13(0),
          m20(0), m21(0), m22(0), m23(0),
          m30(0), m31(0), m32(0), m33(0) {}

    Matrix4x4::Matrix4x4(float data[])
        : m00(data[0]),  m01(data[1]),  m02(data[2]),  m03(data[3]),
          m10(data[4]),  m11(data[5]),  m12(data[6]),  m13(data[7]),
          m20(data[8]),  m21(data[9]),  m22(data[10]), m23(data[11]),
          m30(data[12]), m31(data[13]), m32(data[14]), m33(data[15]) {}

    Matrix4x4::Matrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33)
        : m00(m00), m01(m01), m02(m02), m03(m03),
          m10(m10), m11(m11), m12(m12), m13(m13),
          m20(m20), m21(m21), m22(m22), m23(m23),
          m30(m30), m31(m31), m32(m32), m33(m33) {}

    Matrix4x4 Matrix4x4::Zero()
    {
        return Matrix4x4(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0);
    }

    Matrix4x4 Matrix4x4::Identity()
    {
        return Matrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    Matrix4x4 Matrix4x4::Translate(Vector3 v)
    {
        return Matrix4x4(
            1, 0, 0, v.x,
            0, 1, 0, v.y,
            0, 0, 1, v.z,
            0, 0, 0, 1);
    }

    Matrix4x4 Matrix4x4::Scale(Vector3 scale)
    {
        return Matrix4x4(
            scale.x, 0,       0,       0,
            0,       scale.y, 0,       0,
            0,       0,       scale.z, 0,
            0,       0,       0,       1);
    }

    Matrix4x4 Matrix4x4::RotateX(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix4x4(
            1, 0,  0, 0,
            0, c, -s, 0,
            0, s,  c, 0,
            0, 0,  0, 1);
    }

    Matrix4x4 Matrix4x4::RotateY(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix4x4(
             c, 0, s, 0,
             0, 1, 0, 0,
            -s, 0, c, 0,
             0, 0, 0, 1);
    }

    Matrix4x4 Matrix4x4::RotateZ(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix4x4(
            c, -s, 0, 0,
            s,  c, 0, 0,
            0,  0, 1, 0,
            0,  0, 0, 1);
    }

    Matrix4x4 Matrix4x4::Rotate(Quaternion q)
    {
        float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
        float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
        float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

        return Matrix4x4(
            1 - 2*(yy+zz),   2*(xy-wz),     2*(xz+wy),   0,
              2*(xy+wz),   1 - 2*(xx+zz),   2*(yz-wx),   0,
              2*(xz-wy),     2*(yz+wx),   1 - 2*(xx+yy), 0,
            0,             0,             0,             1);
    }

    Matrix4x4 Matrix4x4::TRS(Vector3 pos, Quaternion rot, Vector3 scale)
    {
        return Translate(pos) * Rotate(rot) * Scale(scale);
    }

    Matrix4x4 Matrix4x4::Perspective(float fovY, float aspect, float near, float far)
    {
        float tanHalf = tan(fovY * 0.5f);
        float r = far - near;
        return Matrix4x4(
            1.0f / (aspect * tanHalf), 0,               0,                         0,
            0,                         1.0f / tanHalf,  0,                         0,
            0,                         0,              -(far + near) / r,          -1,
            0,                         0,              -(2.0f * far * near) / r,   0);
    }

    Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float near, float far)
    {
        float rml = right - left;
        float tmb = top - bottom;
        float fmn = far - near;
        return Matrix4x4(
            2.0f / rml,                0,                        0,                    0,
            0,                         2.0f / tmb,               0,                    0,
            0,                         0,                       -2.0f / fmn,           0,
            -(right + left) / rml,    -(top + bottom) / tmb,   -(far + near) / fmn,   1);
    }

    Matrix4x4 Matrix4x4::LookAt(Vector3 eye, Vector3 center, Vector3 up)
    {
        Vector3 f = Vector3::Normalized(center - eye);
        Vector3 r = Vector3::Normalized(Vector3::Cross(f, up));
        Vector3 u = Vector3::Cross(r, f);
        return Matrix4x4(
             r.x,  r.y,  r.z, -Vector3::Dot(r, eye),
             u.x,  u.y,  u.z, -Vector3::Dot(u, eye),
            -f.x, -f.y, -f.z,  Vector3::Dot(f, eye),
             0,    0,    0,    1);
    }

    Matrix4x4 Matrix4x4::Transpose(Matrix4x4 mat)
    {
        return Matrix4x4(
            mat.m00, mat.m10, mat.m20, mat.m30,
            mat.m01, mat.m11, mat.m21, mat.m31,
            mat.m02, mat.m12, mat.m22, mat.m32,
            mat.m03, mat.m13, mat.m23, mat.m33);
    }

    float Matrix4x4::Determinant(Matrix4x4 mat)
    {
        float s0 = mat.m00 * mat.m11 - mat.m01 * mat.m10;
        float s1 = mat.m00 * mat.m12 - mat.m02 * mat.m10;
        float s2 = mat.m00 * mat.m13 - mat.m03 * mat.m10;
        float s3 = mat.m01 * mat.m12 - mat.m02 * mat.m11;
        float s4 = mat.m01 * mat.m13 - mat.m03 * mat.m11;
        float s5 = mat.m02 * mat.m13 - mat.m03 * mat.m12;

        float c0 = mat.m20 * mat.m31 - mat.m21 * mat.m30;
        float c1 = mat.m20 * mat.m32 - mat.m22 * mat.m30;
        float c2 = mat.m20 * mat.m33 - mat.m23 * mat.m30;
        float c3 = mat.m21 * mat.m32 - mat.m22 * mat.m31;
        float c4 = mat.m21 * mat.m33 - mat.m23 * mat.m31;
        float c5 = mat.m22 * mat.m33 - mat.m23 * mat.m32;

        return s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;
    }

    Matrix4x4 Matrix4x4::Inverse(Matrix4x4 mat)
    {
        float s0 = mat.m00 * mat.m11 - mat.m01 * mat.m10;
        float s1 = mat.m00 * mat.m12 - mat.m02 * mat.m10;
        float s2 = mat.m00 * mat.m13 - mat.m03 * mat.m10;
        float s3 = mat.m01 * mat.m12 - mat.m02 * mat.m11;
        float s4 = mat.m01 * mat.m13 - mat.m03 * mat.m11;
        float s5 = mat.m02 * mat.m13 - mat.m03 * mat.m12;

        float c0 = mat.m20 * mat.m31 - mat.m21 * mat.m30;
        float c1 = mat.m20 * mat.m32 - mat.m22 * mat.m30;
        float c2 = mat.m20 * mat.m33 - mat.m23 * mat.m30;
        float c3 = mat.m21 * mat.m32 - mat.m22 * mat.m31;
        float c4 = mat.m21 * mat.m33 - mat.m23 * mat.m31;
        float c5 = mat.m22 * mat.m33 - mat.m23 * mat.m32;

        float det = s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;
        if (det == 0)
            return Matrix4x4::Zero();

        float invDet = 1.0f / det;

        return Matrix4x4(
            ( mat.m11*c5 - mat.m12*c4 + mat.m13*c3) * invDet,
            (-mat.m01*c5 + mat.m02*c4 - mat.m03*c3) * invDet,
            ( mat.m31*s5 - mat.m32*s4 + mat.m33*s3) * invDet,
            (-mat.m21*s5 + mat.m22*s4 - mat.m23*s3) * invDet,

            (-mat.m10*c5 + mat.m12*c2 - mat.m13*c1) * invDet,
            ( mat.m00*c5 - mat.m02*c2 + mat.m03*c1) * invDet,
            (-mat.m30*s5 + mat.m32*s2 - mat.m33*s1) * invDet,
            ( mat.m20*s5 - mat.m22*s2 + mat.m23*s1) * invDet,

            ( mat.m10*c4 - mat.m11*c2 + mat.m13*c0) * invDet,
            (-mat.m00*c4 + mat.m01*c2 - mat.m03*c0) * invDet,
            ( mat.m30*s4 - mat.m31*s2 + mat.m33*s0) * invDet,
            (-mat.m20*s4 + mat.m21*s2 - mat.m23*s0) * invDet,

            (-mat.m10*c3 + mat.m11*c1 - mat.m12*c0) * invDet,
            ( mat.m00*c3 - mat.m01*c1 + mat.m02*c0) * invDet,
            (-mat.m30*s3 + mat.m31*s1 - mat.m32*s0) * invDet,
            ( mat.m20*s3 - mat.m21*s1 + mat.m22*s0) * invDet);
    }

    Vector4 Matrix4x4::MultiplyVector4(Matrix4x4 mat, Vector4 v)
    {
        return Vector4(
            mat.m00*v.x + mat.m01*v.y + mat.m02*v.z + mat.m03*v.w,
            mat.m10*v.x + mat.m11*v.y + mat.m12*v.z + mat.m13*v.w,
            mat.m20*v.x + mat.m21*v.y + mat.m22*v.z + mat.m23*v.w,
            mat.m30*v.x + mat.m31*v.y + mat.m32*v.z + mat.m33*v.w);
    }

    Vector3 Matrix4x4::MultiplyPoint(Matrix4x4 mat, Vector3 v)
    {
        float w = mat.m30*v.x + mat.m31*v.y + mat.m32*v.z + mat.m33;
        float invW = (w != 0) ? 1.0f / w : 1.0f;
        return Vector3(
            (mat.m00*v.x + mat.m01*v.y + mat.m02*v.z + mat.m03) * invW,
            (mat.m10*v.x + mat.m11*v.y + mat.m12*v.z + mat.m13) * invW,
            (mat.m20*v.x + mat.m21*v.y + mat.m22*v.z + mat.m23) * invW);
    }

    Vector3 Matrix4x4::MultiplyVector(Matrix4x4 mat, Vector3 v)
    {
        return Vector3(
            mat.m00*v.x + mat.m01*v.y + mat.m02*v.z,
            mat.m10*v.x + mat.m11*v.y + mat.m12*v.z,
            mat.m20*v.x + mat.m21*v.y + mat.m22*v.z);
    }

    float& Matrix4x4::operator()(int row, int col)       { return m[row][col]; }
    float  Matrix4x4::operator()(int row, int col) const { return m[row][col]; }

    struct Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 rhs)
    {
        for (int i = 0; i < 16; i++) data[i] += rhs.data[i];
        return *this;
    }

    struct Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 rhs)
    {
        for (int i = 0; i < 16; i++) data[i] -= rhs.data[i];
        return *this;
    }

    struct Matrix4x4& Matrix4x4::operator*=(const float rhs)
    {
        for (int i = 0; i < 16; i++) data[i] *= rhs;
        return *this;
    }

    struct Matrix4x4& Matrix4x4::operator/=(const float rhs)
    {
        for (int i = 0; i < 16; i++) data[i] /= rhs;
        return *this;
    }

    Matrix4x4 operator+(Matrix4x4 lhs, const Matrix4x4 rhs) { return lhs += rhs; }
    Matrix4x4 operator-(Matrix4x4 lhs, const Matrix4x4 rhs) { return lhs -= rhs; }
    Matrix4x4 operator*(Matrix4x4 lhs, const float rhs)     { return lhs *= rhs; }
    Matrix4x4 operator*(const float lhs, Matrix4x4 rhs)     { return rhs *= lhs; }
    Matrix4x4 operator/(Matrix4x4 lhs, const float rhs)     { return lhs /= rhs; }

    Matrix4x4 operator*(Matrix4x4 lhs, const Matrix4x4 rhs)
    {
        return Matrix4x4(
            lhs.m00*rhs.m00 + lhs.m01*rhs.m10 + lhs.m02*rhs.m20 + lhs.m03*rhs.m30,
            lhs.m00*rhs.m01 + lhs.m01*rhs.m11 + lhs.m02*rhs.m21 + lhs.m03*rhs.m31,
            lhs.m00*rhs.m02 + lhs.m01*rhs.m12 + lhs.m02*rhs.m22 + lhs.m03*rhs.m32,
            lhs.m00*rhs.m03 + lhs.m01*rhs.m13 + lhs.m02*rhs.m23 + lhs.m03*rhs.m33,

            lhs.m10*rhs.m00 + lhs.m11*rhs.m10 + lhs.m12*rhs.m20 + lhs.m13*rhs.m30,
            lhs.m10*rhs.m01 + lhs.m11*rhs.m11 + lhs.m12*rhs.m21 + lhs.m13*rhs.m31,
            lhs.m10*rhs.m02 + lhs.m11*rhs.m12 + lhs.m12*rhs.m22 + lhs.m13*rhs.m32,
            lhs.m10*rhs.m03 + lhs.m11*rhs.m13 + lhs.m12*rhs.m23 + lhs.m13*rhs.m33,

            lhs.m20*rhs.m00 + lhs.m21*rhs.m10 + lhs.m22*rhs.m20 + lhs.m23*rhs.m30,
            lhs.m20*rhs.m01 + lhs.m21*rhs.m11 + lhs.m22*rhs.m21 + lhs.m23*rhs.m31,
            lhs.m20*rhs.m02 + lhs.m21*rhs.m12 + lhs.m22*rhs.m22 + lhs.m23*rhs.m32,
            lhs.m20*rhs.m03 + lhs.m21*rhs.m13 + lhs.m22*rhs.m23 + lhs.m23*rhs.m33,

            lhs.m30*rhs.m00 + lhs.m31*rhs.m10 + lhs.m32*rhs.m20 + lhs.m33*rhs.m30,
            lhs.m30*rhs.m01 + lhs.m31*rhs.m11 + lhs.m32*rhs.m21 + lhs.m33*rhs.m31,
            lhs.m30*rhs.m02 + lhs.m31*rhs.m12 + lhs.m32*rhs.m22 + lhs.m33*rhs.m32,
            lhs.m30*rhs.m03 + lhs.m31*rhs.m13 + lhs.m32*rhs.m23 + lhs.m33*rhs.m33);
    }

    Vector4 operator*(Matrix4x4 lhs, const Vector4 rhs)
    {
        return Matrix4x4::MultiplyVector4(lhs, rhs);
    }

    bool operator==(const Matrix4x4 lhs, const Matrix4x4 rhs)
    {
        for (int i = 0; i < 16; i++)
            if (lhs.data[i] != rhs.data[i]) return false;
        return true;
    }

    bool operator!=(const Matrix4x4 lhs, const Matrix4x4 rhs)
    {
        return !(lhs == rhs);
    }
}
