#include "raytracer/geometry/vec.h"
#include "raytracer/geometry/ray.h"
#include "raytracer/geometry/shapes/sphere.h"
#include "raytracer/lights/light.h"
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
    constexpr int width { 480 };
    constexpr int height { 270 };
    // Aspect raio
    constexpr float aspectRatio { static_cast<float>(width) / static_cast<float>(height) };
    
    // Field of View
    constexpr float fovDegress { 90.0f }; // Default: 90 | Limit fov between 1 and 179 when accepting user input
    constexpr float fovRadians { fovDegress * static_cast<float>(M_PI) / 180.0f };
    
    // Set viewport size
    constexpr float viewportHeight { 2.0f };
    constexpr float viewportWidth { viewportHeight * aspectRatio };

    // Calculate focal length
    float focalLength { viewportHeight / (2.0f * tan(fovRadians / 2.0f)) };
    
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

    // Set ray origin
    Vec3 origin(0.0f, 0.0f, 0.0f);

    // Object
    Sphere sphere(Vec3(0.0f, 0.0f, 2.0f), 0.5f);

    // Light
    Light light(Vec3(1.0f, -1.0f, 0.0f));

    // Iterating over every pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float viewportCord[2]  {
                float(x) / float(width),
                float(y) / float(height)
            };
            
            // Adjust range from 0 -> 1 to -1 -> 1
            viewportCord[0] = viewportCord[0] * 2.0f - 1.0f;
            viewportCord[1] = -(viewportCord[1] * 2.0f - 1.0f); // Flip from -1 to 1 since ppm writes top-left to bottom-right

            // Calculate direction
            Vec3 direction { 
                Vec3(viewportWidth * viewportCord[0], viewportHeight * viewportCord[1], focalLength) - // viewport Vec3(x axis, y axis, 0)
                origin 
            };

            // Collision check/color calculation
            Ray ray(origin, direction);
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