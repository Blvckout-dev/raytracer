#ifndef RAY_H
#define RAY_H

#include "vec.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

    Vec3 at(float t) const {
        return origin + direction * t;
    }
};

#endif