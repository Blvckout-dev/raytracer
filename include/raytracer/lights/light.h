#ifndef LIGHT_H
#define LIGHT_H

#include "raytracer/geometry/vec.h"

using vec::Vec3;

struct Light {
    Vec3 Direction;
    Vec3 Color;
    float Intensity;

    Light(const Vec3& dir, const Vec3& col = Vec3(1.0f, 1.0f, 1.0f), float intens = 1.0f)
        : Direction(dir.normalized()), Color(col), Intensity(intens) {}
    };

#endif