#include "renderer.h"
#include "geometry/vec.h"
#include "../scene/scene.h"
#include "geometry/shapes/sphere.h"
#include "camera/camera.h"
#include "lights/light.h"
#include <cmath>

Renderer::Renderer(Scene* scene, uint32_t width, uint32_t height) :
    _scene(scene), _width(width), _height(height)
{
    _aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
    _pixelBuffer.resize(_width * _height);
}

Vec3 Renderer::color(const Ray& ray, const Sphere& sphere, const Light& light) {
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

void Renderer::render()
{
    // Iterating over every pixel
    for (uint32_t y = 0; y < _height; y++) {
        for (uint32_t x = 0; x < _width; x++) {
            // Collision check/color calculation
            Ray ray = _scene->getActiveCamera()->GetRay(x, y);
            Vec3 col = color(ray, *_scene->Sphere, *_scene->getLight());

            // Convert color intensity from percent to rgba 8-bit color channel
            _pixelBuffer[y * _width + x] = (
                (255 << 24) |
                (static_cast<uint8_t>(col.r * 255.99f) << 16) |
                (static_cast<uint8_t>(col.g * 255.99f) << 8) |
                (static_cast<uint8_t>(col.b * 255.99f))
            );
        }
    }
}
