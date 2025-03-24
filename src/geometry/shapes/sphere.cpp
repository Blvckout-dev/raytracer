#include "raytracer/geometry/shapes/sphere.h"

/// @brief Checks if a ray hits the surface
/// @param ray 
/// @return The distance between the ray origin and the surface entry point
float Sphere::hit(const Ray& ray) const {
    // Calculate the coefficients
    float a = ray.direction.dot(ray.direction);
    float b = 2 * ray.origin.dot(ray.direction);
    float c = ray.origin.dot(ray.origin) - (radius * radius);

    // Quadratic formula: -b * +-sqr(b^2 - 4ac) / 2 * a
    // Discriminant: b^2 - 4ac
    float discriminant = (b * b) - 4 * a * c;

    // No intersections when below 0
    if (discriminant < 0)
        return -1.f;

    float tEntry = (-b - sqrt(discriminant)) / (2 * a);
    // float tExit = (-b + sqrt(discriminant)) / (2 * a);

    return tEntry;
}