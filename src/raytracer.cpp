#include "geometry/vec.h"
#include "geometry/ray.h"
#include "geometry/shapes/sphere.h"
#include "lights/light.h"
#include "camera/camera.h"
#include "ui/MainWindow.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <QApplication>
#include <QImage>
#include <QLabel>

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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

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

    // Object
    Sphere sphere(Vec3(0.f, 0.f, 0.f), 0.5f);

    // Light
    Light light(Vec3(1.0f, -1.0f, 0.0f));

    QImage image(width, height, QImage::Format_RGB888);

    // Iterating over every pixel
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            // Collision check/color calculation
            Ray ray = camera.GetRay(x, y);
            Vec3 col = color(ray, sphere, light);

            // Convert color intensity from percent to 8-bit color depth
            int r = static_cast<int>(255.99f * col.x);
            int g = static_cast<int>(255.99f * col.y);
            int b = static_cast<int>(255.99f * col.z);

            // Set pixel color (x, y)
            image.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    MainWindow w;
    w.show();

    w.SetImage(image);
    w.showMenu();

    return app.exec();
}