#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector4.hpp"

namespace Unity
{
    struct Color
    {
        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };
            float data[4];
        };

        inline Color();
        inline Color(float data[]);
        inline Color(float value);
        inline Color(float r, float g, float b);
        inline Color(float r, float g, float b, float a);

        static inline Color Black();
        static inline Color White();
        static inline Color Red();
        static inline Color Green();
        static inline Color Blue();
        static inline Color Yellow();
        static inline Color Cyan();
        static inline Color Magenta();
        static inline Color Gray();
        static inline Color Clear();

        static inline Color   Lerp(Color a, Color b, float t);
        static inline Color   LerpUnclamped(Color a, Color b, float t);
        static inline Color   Clamp(Color c);
        static inline float   GrayValue(Color c);
        static inline Color   Invert(Color c);
        static inline Color   Desaturate(Color c);
        static inline Color   Max(Color a, Color b);
        static inline Color   Min(Color a, Color b);
        static inline Color   Alpha(Color c, float a);
        static inline Color   FromHSV(float h, float s, float v, float a);
        static inline void    ToHSV(Color c, float &h, float &s, float &v);
        static inline Color   FromHex(unsigned int hex);
        static inline Vector4 ToVector4(Color c);
        static inline Color   FromVector4(Vector4 v);

        inline struct Color& operator+=(const float rhs);
        inline struct Color& operator-=(const float rhs);
        inline struct Color& operator*=(const float rhs);
        inline struct Color& operator/=(const float rhs);
        inline struct Color& operator+=(const Color rhs);
        inline struct Color& operator-=(const Color rhs);
        inline struct Color& operator*=(const Color rhs);
    };

    inline Color operator-(Color rhs);
    inline Color operator+(Color lhs, const float rhs);
    inline Color operator-(Color lhs, const float rhs);
    inline Color operator*(Color lhs, const float rhs);
    inline Color operator/(Color lhs, const float rhs);
    inline Color operator+(const float lhs, Color rhs);
    inline Color operator*(const float lhs, Color rhs);
    inline Color operator+(Color lhs, const Color rhs);
    inline Color operator-(Color lhs, const Color rhs);
    inline Color operator*(Color lhs, const Color rhs);
    inline bool  operator==(const Color lhs, const Color rhs);
    inline bool  operator!=(const Color lhs, const Color rhs);


    Color::Color() : r(0), g(0), b(0), a(1) {}
    Color::Color(float data[]) : r(data[0]), g(data[1]), b(data[2]), a(data[3]) {}
    Color::Color(float value) : r(value), g(value), b(value), a(1) {}
    Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    Color Color::Black()   { return Color(0, 0, 0, 1);    }
    Color Color::White()   { return Color(1, 1, 1, 1);    }
    Color Color::Red()     { return Color(1, 0, 0, 1);    }
    Color Color::Green()   { return Color(0, 1, 0, 1);    }
    Color Color::Blue()    { return Color(0, 0, 1, 1);    }
    Color Color::Yellow()  { return Color(1, 1, 0, 1);    }
    Color Color::Cyan()    { return Color(0, 1, 1, 1);    }
    Color Color::Magenta() { return Color(1, 0, 1, 1);    }
    Color Color::Gray()    { return Color(0.5f, 0.5f, 0.5f, 1); }
    Color Color::Clear()   { return Color(0, 0, 0, 0);    }

    Color Color::Lerp(Color a, Color b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return LerpUnclamped(a, b, t);
    }

    Color Color::LerpUnclamped(Color a, Color b, float t)
    {
        return Color(
            a.r + (b.r - a.r) * t,
            a.g + (b.g - a.g) * t,
            a.b + (b.b - a.b) * t,
            a.a + (b.a - a.a) * t);
    }

    Color Color::Clamp(Color c)
    {
        float r = c.r < 0 ? 0 : (c.r > 1 ? 1 : c.r);
        float g = c.g < 0 ? 0 : (c.g > 1 ? 1 : c.g);
        float b = c.b < 0 ? 0 : (c.b > 1 ? 1 : c.b);
        float a = c.a < 0 ? 0 : (c.a > 1 ? 1 : c.a);
        return Color(r, g, b, a);
    }

    float Color::GrayValue(Color c)
    {
        return c.r * 0.299f + c.g * 0.587f + c.b * 0.114f;
    }

    Color Color::Invert(Color c)
    {
        return Color(1 - c.r, 1 - c.g, 1 - c.b, c.a);
    }

    Color Color::Desaturate(Color c)
    {
        float gray = GrayValue(c);
        return Color(gray, gray, gray, c.a);
    }

    Color Color::Max(Color a, Color b)
    {
        return Color(
            a.r > b.r ? a.r : b.r,
            a.g > b.g ? a.g : b.g,
            a.b > b.b ? a.b : b.b,
            a.a > b.a ? a.a : b.a);
    }

    Color Color::Min(Color a, Color b)
    {
        return Color(
            a.r > b.r ? b.r : a.r,
            a.g > b.g ? b.g : a.g,
            a.b > b.b ? b.b : a.b,
            a.a > b.a ? b.a : a.a);
    }

    Color Color::Alpha(Color c, float a)
    {
        return Color(c.r, c.g, c.b, a);
    }

    Color Color::FromHSV(float h, float s, float v, float a)
    {
        if (s == 0)
            return Color(v, v, v, a);

        h = h - floor(h);
        int i = (int)(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - s * f);
        float t = v * (1 - s * (1 - f));

        switch (i % 6)
        {
            case 0: return Color(v, t, p, a);
            case 1: return Color(q, v, p, a);
            case 2: return Color(p, v, t, a);
            case 3: return Color(p, q, v, a);
            case 4: return Color(t, p, v, a);
            default: return Color(v, p, q, a);
        }
    }

    void Color::ToHSV(Color c, float &h, float &s, float &v)
    {
        float maxC = c.r > c.g ? (c.r > c.b ? c.r : c.b) : (c.g > c.b ? c.g : c.b);
        float minC = c.r < c.g ? (c.r < c.b ? c.r : c.b) : (c.g < c.b ? c.g : c.b);
        float delta = maxC - minC;

        v = maxC;
        s = (maxC == 0) ? 0 : delta / maxC;

        if (delta == 0)
        {
            h = 0;
            return;
        }

        if (maxC == c.r)
            h = (c.g - c.b) / delta + (c.g < c.b ? 6 : 0);
        else if (maxC == c.g)
            h = (c.b - c.r) / delta + 2;
        else
            h = (c.r - c.g) / delta + 4;

        h /= 6;
    }

    Color Color::FromHex(unsigned int hex)
    {
        float r = ((hex >> 24) & 0xFF) / 255.0f;
        float g = ((hex >> 16) & 0xFF) / 255.0f;
        float b = ((hex >>  8) & 0xFF) / 255.0f;
        float a = ((hex      ) & 0xFF) / 255.0f;
        return Color(r, g, b, a);
    }

    Vector4 Color::ToVector4(Color c)
    {
        return Vector4(c.r, c.g, c.b, c.a);
    }

    Color Color::FromVector4(Vector4 v)
    {
        return Color(v.x, v.y, v.z, v.w);
    }

    struct Color& Color::operator+=(const float rhs) { r += rhs; g += rhs; b += rhs; a += rhs; return *this; }
    struct Color& Color::operator-=(const float rhs) { r -= rhs; g -= rhs; b -= rhs; a -= rhs; return *this; }
    struct Color& Color::operator*=(const float rhs) { r *= rhs; g *= rhs; b *= rhs; a *= rhs; return *this; }
    struct Color& Color::operator/=(const float rhs) { r /= rhs; g /= rhs; b /= rhs; a /= rhs; return *this; }

    struct Color& Color::operator+=(const Color rhs) { r += rhs.r; g += rhs.g; b += rhs.b; a += rhs.a; return *this; }
    struct Color& Color::operator-=(const Color rhs) { r -= rhs.r; g -= rhs.g; b -= rhs.b; a -= rhs.a; return *this; }
    struct Color& Color::operator*=(const Color rhs) { r *= rhs.r; g *= rhs.g; b *= rhs.b; a *= rhs.a; return *this; }

    Color operator-(Color rhs)                    { return rhs * -1; }
    Color operator+(Color lhs, const float rhs)   { return lhs += rhs; }
    Color operator-(Color lhs, const float rhs)   { return lhs -= rhs; }
    Color operator*(Color lhs, const float rhs)   { return lhs *= rhs; }
    Color operator/(Color lhs, const float rhs)   { return lhs /= rhs; }
    Color operator+(const float lhs, Color rhs)   { return rhs += lhs; }
    Color operator*(const float lhs, Color rhs)   { return rhs *= lhs; }
    Color operator+(Color lhs, const Color rhs)   { return lhs += rhs; }
    Color operator-(Color lhs, const Color rhs)   { return lhs -= rhs; }
    Color operator*(Color lhs, const Color rhs)   { return lhs *= rhs; }

    bool operator==(const Color lhs, const Color rhs)
    {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
    }

    bool operator!=(const Color lhs, const Color rhs)
    {
        return !(lhs == rhs);
    }
}
