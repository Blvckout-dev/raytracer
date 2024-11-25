#include "raytracer/geometry/vec3.h"
#include "raytracer/geometry/ray.h"
#include "raytracer/geometry/shapes/sphere.h"
#include <iostream>
#include <fstream>
#include <cmath>

// Mathematical constants
#define M_PI 3.14159265358979323846 // pi

Vec3 color(const Ray& ray, const Sphere& sphere) {
    if (sphere.hit(ray)) {
        return Vec3(1.0f, 0.0f, 0.0f); // Red
    }

    return Vec3(0.0f, 0.0f, 0.0f); // black background
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
    Vec3 origin(0.0f, 0.0f, -focalLength);
    
    // Anchor for direction calculation
    Vec3 viewportLowerLeftCorner(-viewportWidth / 2, -viewportHeight / 2, 0);

    // Object
    Sphere sphere(Vec3(0.0f, 0.0f, 2.0f), 0.5f);

    // Iterating over every pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float widthPosPercent = float(x) / float(width); // Percent value of the progress on the width
            float heightPosPercent = float(y) / float(height); // Percent value of the progress on the height

            // Calculate direction
            Vec3 direction { 
                viewportLowerLeftCorner + Vec3(viewportWidth * widthPosPercent, 0, 0) // viewport x axis
                + Vec3(0, viewportHeight * heightPosPercent, 0) // viewport y axis
                - origin 
            };

            // Collision check/color calculation
            Ray ray(origin, direction.normalized());
            Vec3 col = color(ray, sphere);

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