#ifndef RENDER_H
#define RENDER_H

#include <cstdint>
#include <vector>

namespace vec {
    template<typename T, size_t N>
    struct Vec;
}
class Ray;
class Sphere;
class Light;
class Scene;

using Vec3 = vec::Vec<float, 3>;

class Renderer {
private:
    Scene* _scene {};
    uint32_t _width {};
    uint32_t _height {};

    float _aspectRatio {};

    std::vector<uint32_t> _pixelBuffer {};

    Vec3 color(const Ray& ray, const Sphere& sphere, const Light& light);

public:
    Renderer(Scene* scene, uint32_t width, uint32_t height);
    ~Renderer() = default;

    void render();

    const std::vector<uint32_t>& getPixelBuffer() const { return _pixelBuffer; }
};

#endif