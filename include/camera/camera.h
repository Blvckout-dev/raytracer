#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/vec.h"
#include "geometry/mat.h"
#include "geometry/transform.h"
#include "geometry/ray.h"

using vec::Vec3;
using vec::Vec4;

enum class FovType {
    Vertical,
    Horizontal
};

class Camera {
private:
    Vec3 _position {};
    Vec3 _forwardDirection {};
    const Vec3 _worldUp { 0.f, 1.f, 0.f };
        
    uint32_t _imageWidth {};
    uint32_t _imageHeight {};

    const float _viewportHeight { 2.0f };
    float _viewportWidth {};

    float _fovDegrees {};
    FovType _fovType { FovType::Vertical };
    float _verticalFovRadians {};

    float _zNear { 0.1f };
    float _zFar { 100.f };

    float _focalLength {};
    float _aspectRatio {};

    Mat4 _projectionMat { 1.f };
    Mat4 _inverseProjectionMat { 1.f };

    Mat4 _viewMat { 1.f };
    Mat4 _inverseViewMat { 1.f };

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
public:
    Camera(
        Vec3 position = Vec3(0.f, 0.f, 0.f),
        Vec3 forwardDirection = Vec3(0.f, 0.f, -1.f),
        uint32_t width = 800,
        uint32_t height = 600,
        float fovDegrees = 90.0f,
        FovType fovType = FovType::Vertical
    );

    void SetFov(float fovDegrees, FovType fovType);
    float GetFov() const { return _fovDegrees; };

    void SetResolution(uint32_t width, uint32_t height);

    Ray GetRay(uint32_t pixelX, uint32_t pixelY) const;
};

#endif
