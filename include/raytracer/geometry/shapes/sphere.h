#ifndef SPHERE_H
#define SPHERE_H

#include "raytracer/geometry/vec.h"
#include "raytracer/geometry/ray.h"

#include <cmath>

class Sphere {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}

    /// <summary>
    /// Check if ray intersects with surface
    /// <returns>Distance from ray origin to sphere surface entry point</returns>
    /// </summary>
    float hit(const Ray& ray) const;
};

#endif