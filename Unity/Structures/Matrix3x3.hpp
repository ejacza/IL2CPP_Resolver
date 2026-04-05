#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.hpp"

namespace Unity
{
    struct Matrix3x3
    {
        union
        {
            struct
            {
                float m00, m01, m02;
                float m10, m11, m12;
                float m20, m21, m22;
            };
            float m[3][3];
            float data[9];
        };

        inline Matrix3x3();
        inline Matrix3x3(float data[]);
        inline Matrix3x3(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);

        static inline Matrix3x3 Zero();
        static inline Matrix3x3 Identity();

        static inline Matrix3x3 Scale(Vector3 scale);
        static inline Matrix3x3 RotateX(float rad);
        static inline Matrix3x3 RotateY(float rad);
        static inline Matrix3x3 RotateZ(float rad);

        static inline Matrix3x3 Transpose(Matrix3x3 mat);
        static inline float     Determinant(Matrix3x3 mat);
        static inline Matrix3x3 Inverse(Matrix3x3 mat);

        static inline Vector3   MultiplyVector(Matrix3x3 mat, Vector3 v);

        inline float& operator()(int row, int col);
        inline float  operator()(int row, int col) const;

        inline struct Matrix3x3& operator+=(const Matrix3x3 rhs);
        inline struct Matrix3x3& operator-=(const Matrix3x3 rhs);
        inline struct Matrix3x3& operator*=(const float rhs);
        inline struct Matrix3x3& operator/=(const float rhs);
    };

    inline Matrix3x3 operator+(Matrix3x3 lhs, const Matrix3x3 rhs);
    inline Matrix3x3 operator-(Matrix3x3 lhs, const Matrix3x3 rhs);
    inline Matrix3x3 operator*(Matrix3x3 lhs, const float rhs);
    inline Matrix3x3 operator*(const float lhs, Matrix3x3 rhs);
    inline Matrix3x3 operator/(Matrix3x3 lhs, const float rhs);
    inline Matrix3x3 operator*(Matrix3x3 lhs, const Matrix3x3 rhs);
    inline Vector3   operator*(Matrix3x3 lhs, const Vector3 rhs);
    inline bool      operator==(const Matrix3x3 lhs, const Matrix3x3 rhs);
    inline bool      operator!=(const Matrix3x3 lhs, const Matrix3x3 rhs);


    Matrix3x3::Matrix3x3()
        : m00(0), m01(0), m02(0),
          m10(0), m11(0), m12(0),
          m20(0), m21(0), m22(0) {}

    Matrix3x3::Matrix3x3(float data[])
        : m00(data[0]), m01(data[1]), m02(data[2]),
          m10(data[3]), m11(data[4]), m12(data[5]),
          m20(data[6]), m21(data[7]), m22(data[8]) {}

    Matrix3x3::Matrix3x3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22)
        : m00(m00), m01(m01), m02(m02),
          m10(m10), m11(m11), m12(m12),
          m20(m20), m21(m21), m22(m22) {}

    Matrix3x3 Matrix3x3::Zero()
    {
        return Matrix3x3(
            0, 0, 0,
            0, 0, 0,
            0, 0, 0);
    }

    Matrix3x3 Matrix3x3::Identity()
    {
        return Matrix3x3(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1);
    }

    Matrix3x3 Matrix3x3::Scale(Vector3 scale)
    {
        return Matrix3x3(
            scale.x, 0,       0,
            0,       scale.y, 0,
            0,       0,       scale.z);
    }

    Matrix3x3 Matrix3x3::RotateX(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix3x3(
            1, 0,  0,
            0, c, -s,
            0, s,  c);
    }

    Matrix3x3 Matrix3x3::RotateY(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix3x3(
             c, 0, s,
             0, 1, 0,
            -s, 0, c);
    }

    Matrix3x3 Matrix3x3::RotateZ(float rad)
    {
        float c = cos(rad);
        float s = sin(rad);
        return Matrix3x3(
            c, -s, 0,
            s,  c, 0,
            0,  0, 1);
    }

    Matrix3x3 Matrix3x3::Transpose(Matrix3x3 mat)
    {
        return Matrix3x3(
            mat.m00, mat.m10, mat.m20,
            mat.m01, mat.m11, mat.m21,
            mat.m02, mat.m12, mat.m22);
    }

    float Matrix3x3::Determinant(Matrix3x3 mat)
    {
        return mat.m00 * (mat.m11 * mat.m22 - mat.m12 * mat.m21)
             - mat.m01 * (mat.m10 * mat.m22 - mat.m12 * mat.m20)
             + mat.m02 * (mat.m10 * mat.m21 - mat.m11 * mat.m20);
    }

    Matrix3x3 Matrix3x3::Inverse(Matrix3x3 mat)
    {
        float det = Determinant(mat);
        if (det == 0)
            return Matrix3x3::Zero();

        float invDet = 1.0f / det;

        return Matrix3x3(
            (mat.m11 * mat.m22 - mat.m12 * mat.m21) * invDet,
            (mat.m02 * mat.m21 - mat.m01 * mat.m22) * invDet,
            (mat.m01 * mat.m12 - mat.m02 * mat.m11) * invDet,

            (mat.m12 * mat.m20 - mat.m10 * mat.m22) * invDet,
            (mat.m00 * mat.m22 - mat.m02 * mat.m20) * invDet,
            (mat.m02 * mat.m10 - mat.m00 * mat.m12) * invDet,

            (mat.m10 * mat.m21 - mat.m11 * mat.m20) * invDet,
            (mat.m01 * mat.m20 - mat.m00 * mat.m21) * invDet,
            (mat.m00 * mat.m11 - mat.m01 * mat.m10) * invDet);
    }

    Vector3 Matrix3x3::MultiplyVector(Matrix3x3 mat, Vector3 v)
    {
        return Vector3(
            mat.m00 * v.x + mat.m01 * v.y + mat.m02 * v.z,
            mat.m10 * v.x + mat.m11 * v.y + mat.m12 * v.z,
            mat.m20 * v.x + mat.m21 * v.y + mat.m22 * v.z);
    }

    float& Matrix3x3::operator()(int row, int col)       { return m[row][col]; }
    float  Matrix3x3::operator()(int row, int col) const { return m[row][col]; }

    struct Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 rhs)
    {
        for (int i = 0; i < 9; i++) data[i] += rhs.data[i];
        return *this;
    }

    struct Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 rhs)
    {
        for (int i = 0; i < 9; i++) data[i] -= rhs.data[i];
        return *this;
    }

    struct Matrix3x3& Matrix3x3::operator*=(const float rhs)
    {
        for (int i = 0; i < 9; i++) data[i] *= rhs;
        return *this;
    }

    struct Matrix3x3& Matrix3x3::operator/=(const float rhs)
    {
        for (int i = 0; i < 9; i++) data[i] /= rhs;
        return *this;
    }

    Matrix3x3 operator+(Matrix3x3 lhs, const Matrix3x3 rhs) { return lhs += rhs; }
    Matrix3x3 operator-(Matrix3x3 lhs, const Matrix3x3 rhs) { return lhs -= rhs; }
    Matrix3x3 operator*(Matrix3x3 lhs, const float rhs)     { return lhs *= rhs; }
    Matrix3x3 operator*(const float lhs, Matrix3x3 rhs)     { return rhs *= lhs; }
    Matrix3x3 operator/(Matrix3x3 lhs, const float rhs)     { return lhs /= rhs; }

    Matrix3x3 operator*(Matrix3x3 lhs, const Matrix3x3 rhs)
    {
        return Matrix3x3(
            lhs.m00*rhs.m00 + lhs.m01*rhs.m10 + lhs.m02*rhs.m20,
            lhs.m00*rhs.m01 + lhs.m01*rhs.m11 + lhs.m02*rhs.m21,
            lhs.m00*rhs.m02 + lhs.m01*rhs.m12 + lhs.m02*rhs.m22,

            lhs.m10*rhs.m00 + lhs.m11*rhs.m10 + lhs.m12*rhs.m20,
            lhs.m10*rhs.m01 + lhs.m11*rhs.m11 + lhs.m12*rhs.m21,
            lhs.m10*rhs.m02 + lhs.m11*rhs.m12 + lhs.m12*rhs.m22,

            lhs.m20*rhs.m00 + lhs.m21*rhs.m10 + lhs.m22*rhs.m20,
            lhs.m20*rhs.m01 + lhs.m21*rhs.m11 + lhs.m22*rhs.m21,
            lhs.m20*rhs.m02 + lhs.m21*rhs.m12 + lhs.m22*rhs.m22);
    }

    Vector3 operator*(Matrix3x3 lhs, const Vector3 rhs)
    {
        return Matrix3x3::MultiplyVector(lhs, rhs);
    }

    bool operator==(const Matrix3x3 lhs, const Matrix3x3 rhs)
    {
        for (int i = 0; i < 9; i++)
            if (lhs.data[i] != rhs.data[i]) return false;
        return true;
    }

    bool operator!=(const Matrix3x3 lhs, const Matrix3x3 rhs)
    {
        return !(lhs == rhs);
    }
}
