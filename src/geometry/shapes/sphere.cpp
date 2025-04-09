#include "raytracer/geometry/shapes/sphere.h"

/// @brief Checks if a ray hits the surface
/// @param ray 
/// @return The distance between the ray origin and the surface entry point
float Sphere::hit(const Ray& ray) const {
    // Vector from sphere center to origin
    Vec3 oc { ray.origin - center };

    // Calculate the coefficients
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - (radius * radius);

    // Quadratic formula: -b * +-sqr(b^2 - 4ac) / 2 * a
    // Discriminant: b^2 - 4ac
    float discriminant = (b * b) - 4 * a * c;

    // No intersections when below 0
    if (discriminant < 0)
        return -1.f;

    float tEntry = (-b - sqrt(discriminant)) / (2.0f * a);
    // float tExit = (-b + sqrt(discriminant)) / (2.0f * a);

    return tEntry;
}