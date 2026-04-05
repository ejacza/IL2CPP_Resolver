#pragma once

#include "Vector2.hpp"

namespace Unity
{
    struct Rect
    {
        union
        {
            struct
            {
                float x;
                float y;
                float width;
                float height;
            };
            float data[4];
        };

        inline Rect();
        inline Rect(float data[]);
        inline Rect(float x, float y, float width, float height);
        inline Rect(Vector2 position, Vector2 size);

        static inline Rect Zero();

        inline float    Left()    const;
        inline float    Right()   const;
        inline float    Top()     const;
        inline float    Bottom()  const;
        inline Vector2  Min()     const;
        inline Vector2  Max()     const;
        inline Vector2  Center()  const;
        inline Vector2  Position() const;
        inline Vector2  Size()    const;

        static inline bool    Contains(Rect rect, Vector2 point);
        static inline bool    Overlaps(Rect a, Rect b);
        static inline Rect    Intersect(Rect a, Rect b);
        static inline Rect    Union(Rect a, Rect b);
        static inline Rect    Expand(Rect rect, float amount);
        static inline Rect    Expand(Rect rect, float horizontal, float vertical);
        static inline Rect    Translate(Rect rect, Vector2 delta);
        static inline Rect    Scale(Rect rect, float scale);
        static inline Rect    Scale(Rect rect, Vector2 scale);
        static inline Rect    FromMinMax(Vector2 min, Vector2 max);
        static inline Rect    FromCenter(Vector2 center, Vector2 size);

        inline struct Rect& operator+=(const Vector2 rhs);
        inline struct Rect& operator-=(const Vector2 rhs);
    };

    inline Rect operator+(Rect lhs, const Vector2 rhs);
    inline Rect operator-(Rect lhs, const Vector2 rhs);
    inline bool operator==(const Rect lhs, const Rect rhs);
    inline bool operator!=(const Rect lhs, const Rect rhs);


    Rect::Rect() : x(0), y(0), width(0), height(0) {}
    Rect::Rect(float data[]) : x(data[0]), y(data[1]), width(data[2]), height(data[3]) {}
    Rect::Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
    Rect::Rect(Vector2 position, Vector2 size) : x(position.x), y(position.y), width(size.x), height(size.y) {}

    Rect Rect::Zero() { return Rect(0, 0, 0, 0); }

    float   Rect::Left()     const { return x; }
    float   Rect::Right()    const { return x + width; }
    float   Rect::Top()      const { return y; }
    float   Rect::Bottom()   const { return y + height; }
    Vector2 Rect::Min()      const { return Vector2(x, y); }
    Vector2 Rect::Max()      const { return Vector2(x + width, y + height); }
    Vector2 Rect::Center()   const { return Vector2(x + width * 0.5f, y + height * 0.5f); }
    Vector2 Rect::Position() const { return Vector2(x, y); }
    Vector2 Rect::Size()     const { return Vector2(width, height); }

    bool Rect::Contains(Rect rect, Vector2 point)
    {
        return point.x >= rect.x && point.x <= rect.x + rect.width
            && point.y >= rect.y && point.y <= rect.y + rect.height;
    }

    bool Rect::Overlaps(Rect a, Rect b)
    {
        return a.x < b.x + b.width  && a.x + a.width  > b.x
            && a.y < b.y + b.height && a.y + a.height > b.y;
    }

    Rect Rect::Intersect(Rect a, Rect b)
    {
        float x1 = a.x > b.x ? a.x : b.x;
        float y1 = a.y > b.y ? a.y : b.y;
        float x2 = a.x + a.width  < b.x + b.width  ? a.x + a.width  : b.x + b.width;
        float y2 = a.y + a.height < b.y + b.height ? a.y + a.height : b.y + b.height;
        if (x2 < x1 || y2 < y1)
            return Rect::Zero();
        return Rect(x1, y1, x2 - x1, y2 - y1);
    }

    Rect Rect::Union(Rect a, Rect b)
    {
        float x1 = a.x < b.x ? a.x : b.x;
        float y1 = a.y < b.y ? a.y : b.y;
        float x2 = a.x + a.width  > b.x + b.width  ? a.x + a.width  : b.x + b.width;
        float y2 = a.y + a.height > b.y + b.height ? a.y + a.height : b.y + b.height;
        return Rect(x1, y1, x2 - x1, y2 - y1);
    }

    Rect Rect::Expand(Rect rect, float amount)
    {
        return Rect(rect.x - amount, rect.y - amount, rect.width + amount * 2, rect.height + amount * 2);
    }

    Rect Rect::Expand(Rect rect, float horizontal, float vertical)
    {
        return Rect(rect.x - horizontal, rect.y - vertical, rect.width + horizontal * 2, rect.height + vertical * 2);
    }

    Rect Rect::Translate(Rect rect, Vector2 delta)
    {
        return Rect(rect.x + delta.x, rect.y + delta.y, rect.width, rect.height);
    }

    Rect Rect::Scale(Rect rect, float scale)
    {
        return Rect(rect.x * scale, rect.y * scale, rect.width * scale, rect.height * scale);
    }

    Rect Rect::Scale(Rect rect, Vector2 scale)
    {
        return Rect(rect.x * scale.x, rect.y * scale.y, rect.width * scale.x, rect.height * scale.y);
    }

    Rect Rect::FromMinMax(Vector2 min, Vector2 max)
    {
        return Rect(min.x, min.y, max.x - min.x, max.y - min.y);
    }

    Rect Rect::FromCenter(Vector2 center, Vector2 size)
    {
        return Rect(center.x - size.x * 0.5f, center.y - size.y * 0.5f, size.x, size.y);
    }

    struct Rect& Rect::operator+=(const Vector2 rhs) { x += rhs.x; y += rhs.y; return *this; }
    struct Rect& Rect::operator-=(const Vector2 rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    Rect operator+(Rect lhs, const Vector2 rhs) { return lhs += rhs; }
    Rect operator-(Rect lhs, const Vector2 rhs) { return lhs -= rhs; }

    bool operator==(const Rect lhs, const Rect rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
    }

    bool operator!=(const Rect lhs, const Rect rhs)
    {
        return !(lhs == rhs);
    }
}
