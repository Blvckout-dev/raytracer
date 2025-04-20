#ifndef RAY_H
#define RAY_H

#include "vec.h"

struct Ray {
    Vec3 Origin;
    Vec3 Direction;

    Ray(const Vec3& origin, const Vec3& direction) : Origin(origin), Direction(direction) {}

    Vec3 At(float t) const {
        return Origin + Direction * t;
    }
};

#endif