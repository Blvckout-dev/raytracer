#include "raytracer/geometry/shapes/sphere.h"

float Sphere::hit(const Ray& ray) const {
    Vec3 oc = ray.origin - center; // Vector from ray.origin to sphere center

    float t = oc.dot(ray.direction); // Closest ray pos to sphere center
    float d2 = oc.dot(oc) - t * t;
    float r2 = radius * radius;
    
    // Compare d^2 with r^2 to determin if the ray is able to hit the sphere at all
    if (d2 > r2)
        return 0.0f;

    // Ray is tangent to sphere
    if (d2 == r2)
        return t;

    // float tEntry = t - std::sqrt(r2 - d2); // entry point
    // float tExit = t + std::sqrt(r2 - d2); // exit point

    return t - std::sqrt(r2 - d2); // entry point
}