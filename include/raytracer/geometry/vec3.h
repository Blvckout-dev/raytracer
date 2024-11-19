#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(float t) const { 
        return Vec3(x * t, y * t, z * t);
    }

    // Scalar product
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Vector length
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalization
    Vec3 normalized() const {
        float len = length();
        return Vec3(x / len, y / len, z / len);
    }
};

#endif