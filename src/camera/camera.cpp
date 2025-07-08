#include "camera/camera.h"
#include <algorithm>

Camera::Camera(
    Vec3 position,
    Vec3 forwardDirection,
    uint32_t width,
    uint32_t height,
    float fovDegrees,
    FovType fovType
) :
    _position(position),
    _forwardDirection(forwardDirection.normalized()) 
{
    SetResolution(width, height);
    SetFov(fovDegrees, fovType);
}

void Camera::UpdateViewMatrix()
{
	_viewMat = lookAt(_position, _position + _forwardDirection, _worldUp);
	_inverseViewMat = _viewMat.inversed();
}

void Camera::UpdateProjectionMatrix()
{
	_projectionMat = perspective<float>(_verticalFovRadians, _aspectRatio, _zNear, _zFar);
	_inverseProjectionMat = _projectionMat.inversed();
}

void Camera::SetFov(float fovDegrees, FovType fovType) {
    _fovDegrees = std::clamp(fovDegrees, 1.0f, 179.0f);
    _fovType = fovType;

    if (_fovType == FovType::Horizontal) {
        float fovRad = _fovDegrees * (static_cast<float>(M_PI)  / 180.0f);
        _verticalFovRadians = 2.0f * atanf(tanf(fovRad / 2.0f) / _aspectRatio);
    } else {
        _verticalFovRadians = _fovDegrees * (static_cast<float>(M_PI)  / 180.0f);
    }

    _focalLength = _viewportHeight / (2.0f * tan(_verticalFovRadians / 2.0f));

    UpdateProjectionMatrix();
}

void Camera::SetResolution(uint32_t width, uint32_t height) {
    if (width == _imageWidth && height == _imageHeight)
		return;

	_imageWidth = width;
	_imageHeight = height;

    _aspectRatio = static_cast<float>(_imageWidth) / static_cast<float>(_imageHeight);
    _viewportWidth = _viewportHeight * _aspectRatio;

    UpdateViewMatrix();
	UpdateProjectionMatrix();
}

Ray Camera::GetRay(uint32_t pixelX, uint32_t pixelY) const {
    // Compute normalized pixel coordinates [0, 1]
    float u = (pixelX + 0.5f) / _imageWidth;
    float v = (pixelY + 0.5f) / _imageHeight;

    // Compute point on image plane in camera space
    Vec3 imagePlanePoint = Vec3(
        (u - 0.5f) * _viewportWidth,
        (0.5f - v) * _viewportHeight,
        -_focalLength  // Image plane at distance focalLength
    );

    // Transform direction to world space
    Vec4 rayDirWorld4 = _inverseViewMat * Vec4(imagePlanePoint.normalized(), 0.0f);
    Vec3 rayDirWorld = Vec3(rayDirWorld4).normalized();

    return { _position, rayDirWorld };
}
