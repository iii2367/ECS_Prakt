#ifndef VEC4_H
#define VEC4_H

struct Vec4
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float w = 0.0;

    Vec4& operator=(const Vec4& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    Vec4 operator+(const Vec4& other) const
    {
        return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Vec4 operator-(const Vec4& other) const
    {
        return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Vec4 operator*(float scalar) const
    {
        return Vec4{x * scalar, y * scalar, z * scalar, w * scalar};
    }
 
    Vec4 operator/(float scalar) const
    {
        return Vec4{x / scalar, y / scalar, z / scalar, w / scalar};
    }
};

#endif
