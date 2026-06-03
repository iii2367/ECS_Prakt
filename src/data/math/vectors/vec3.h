#ifndef VEC3_H
#define VEC3_H

struct Vec3
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vec3& operator=(const Vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vec3 operator+(const Vec3& other) const
    {
        return Vec3{x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3& other) const
    {
        return Vec3{x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(float scalar) const
    {
        return Vec3{x * scalar, y * scalar, z * scalar};
    }
 
    Vec3 operator/(float scalar) const
    {
        return Vec3{x / scalar, y / scalar, z / scalar};
    }

};

#endif
