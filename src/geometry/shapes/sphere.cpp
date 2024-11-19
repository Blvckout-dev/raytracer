#include "raytracer/geometry/shapes/sphere.h"

bool Sphere::hit(const Ray& ray) const {
    Vec3 oc = ray.origin - center; // Vector from ray.origin to sphere center

    float t = oc.dot(ray.direction); // Closest ray pos to sphere center
    float d2 = oc.dot(oc) - t * t;
    float r2 = radius * radius;
    
    // Compare d^2 with r^2 to determin if ray hits the sphere
    if (d2 > r2)
        return false;
    
    return true;
}