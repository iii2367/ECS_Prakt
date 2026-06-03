#ifndef VEC2_H
#define VEC2_H

struct Vec2
{
    float x = 0.0;
    float y = 0.0;

    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2{x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2{x - other.x, y - other.y};
    }

    Vec2 operator*(float scalar) const
    {
        return Vec2{x * scalar, y * scalar};
    }
 
    Vec2 operator/(float scalar) const
    {
        return Vec2{x / scalar, y / scalar};
    }
};

#endif
