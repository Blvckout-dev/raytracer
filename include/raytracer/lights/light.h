#ifndef LIGHT_H
#define LIGHT_H

#include "raytracer/geometry/vec3.h"

class Light {
    public:
        Vec3 direction;
        Vec3 color;
        float intensity;
    
        Light(const Vec3& dir, const Vec3& col = Vec3(1.0f, 1.0f, 1.0f), float intens = 1.0f)
            : direction(dir.normalized()), color(col), intensity(intens) {}
    };

#endif