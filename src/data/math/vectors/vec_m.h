#ifndef VEC_M_H
#define VEC_M_H

struct Vec
{
    struct Vec2
    {
        float x = 0.0;
        float y = 0.0;

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


        bool operator==(const Vec2& other) const
        {
            return (x == other.x && y == other.y);
        }
    
        bool operator!=(const Vec2& other) const
        {
            return (x != other.x && y != other.y);
        }

        bool operator==(const Vec3& other) const
        {
            return (x == other.x && y == other.y);
        }
    
        bool operator!=(const Vec3& other) const
        {
        return (x != other.x && y != other.y);
    }

    bool operator==(const Vec4& other) const
    {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Vec4& other) const
    {
        return (x != other.x && y != other.y);
    }
};

struct Vec3
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

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

    bool operator==(const Vec2& other) const
    {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Vec2& other) const
    {
        return (x != other.x && y != other.y);
    }

    bool operator==(const Vec3& other) const
    {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Vec3& other) const
    {
        return (x != other.x && y != other.y);
    }

    bool operator==(const Vec4& other) const
    {
        return (x == other.x && y == other.y);
    }
    
    bool operator!=(const Vec4& other) const
    {
        return (x != other.x && y != other.y);
    }
};

struct Vec4
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float w = 0.0;

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
};
#endif
