#ifndef SPHERE_H
#define SPHERE_H

#include "raytracer/geometry/vec3.h"
#include "raytracer/geometry/ray.h"

#include <cmath>

class Sphere {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}

    bool hit(const Ray& ray) const;
};

#endif