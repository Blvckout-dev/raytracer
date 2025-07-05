#include "geometry/vec.h"
#include "geometry/ray.h"
#include "geometry/shapes/sphere.h"
#include "lights/light.h"
#include "camera/camera.h"
#include <iostream>
#include <fstream>
#include <cmath>

using vec::Vec3;

Vec3 color(const Ray& ray, const Sphere& sphere, const Light& light) {
    // Base color of the sphere
    Vec3 baseColor(1.0f, 0.0f, 0.0f);
    
    float t = sphere.hit(ray);
    
    if (t < 0.0f) {
        return Vec3(0.0f, 0.0f, 0.0f); // black background
    }

    // Intersection location
    Vec3 intersection = ray.Origin + ray.Direction * t;

    // Normalized direction vector from sphere.center to intersection location
    Vec3 normal = (intersection - sphere.center).normalized();

    // Angle between the light direction and the surface normal
    float intensity = std::max(normal.dot(-light.Direction), 0.0f) * light.Intensity;

    // Apply lighting effect (combine light color with intensity)
    return baseColor * intensity;
}

int main() {
    // Resolution
    constexpr int width { 800 };
    constexpr int height { 600 };

    // Field of View
    constexpr float fovDegrees { 90.0f };

    // Camera setup
    Camera camera = Camera(
        Vec3(0.f, 0.f, 6.f),
        Vec3(0.0f, 0.0f, -1.0f),
        width,
        height,
        fovDegrees
    );
    
    // Output file
    std::ofstream out("output.ppm", std::ios::out);
    if (!out) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // PPM Header
    out << "P3\n";
    out << width << " " << height << "\n";
    out << "255\n";

    // Object
    Sphere sphere(Vec3(0.f, 0.f, 0.f), 0.5f);

    // Light
    Light light(Vec3(1.0f, -1.0f, 0.0f));

    // Iterating over every pixel
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            // Collision check/color calculation
            Ray ray = camera.GetRay(x, y);
            Vec3 col = color(ray, sphere, light);

            // Convert color intensity from percent to 8-bit color depth
            int ir = static_cast<int>(255.99f * col.x);
            int ig = static_cast<int>(255.99f * col.y);
            int ib = static_cast<int>(255.99f * col.z);

            // Write color channels to output
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close();

    return 0;
}