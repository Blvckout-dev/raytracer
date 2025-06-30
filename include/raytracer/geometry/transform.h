#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat.h"

using vec::Vec3;
using vec::Vec4;

/// @brief Constructs a right-handed view matrix from the given camera parameters.
/// 
/// Builds a look-at view matrix using the camera's position (`eye`), a target point (`target`),
/// and the world's up vector (`worldUp`). Mimics glm::lookAt behavior.
///
/// @param eye The position of the camera.
/// @param target The point the camera is looking at.
/// @param worldUp The world's up direction (default is Vec3(0, 1, 0)).
/// @return A 4x4 view matrix.
inline Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& worldUp = Vec3(0, 1, 0)) {
    Vec3 forward = (target - eye).normalized();
    Vec3 right = forward.cross(worldUp).normalized();
    Vec3 up = right.cross(forward);

    Mat4 view { 1.f };

    view[0] = Vec4(right, 0.0f);
    view[1] = Vec4(up, 0.0f);
    view[2] = Vec4(-forward, 0.0f);
    
    view[3] = Vec4(-right.dot(eye), -up.dot(eye), forward.dot(eye), 1.0f);

    return view;
}

/// @brief Constructs a right-handed perspective projection matrix.
/// 
/// Builds a perspective projection matrix from the field of view, aspect ratio, and clipping planes.
/// Uses a right-handed coordinate system where the camera looks along the -Z axis.
///
/// @tparam T The numeric type (typically float or double).
/// @param verticalFovRadians Vertical field of view in radians.
/// @param aspectRatio Width divided by height of the viewport.
/// @param zNear Distance to the near clipping plane (must be > 0).
/// @param zFar Distance to the far clipping plane (must be > zNear).
/// @return A 4x4 perspective projection matrix.
template <typename T>
Mat4 perspective(T verticalFovRadians, T aspectRatio, T zNear, T zFar) {
    float f = 1.0f / tan(verticalFovRadians / 2.0f);

    Mat4 result;

    result[0][0] = f / aspectRatio;
    result[1][1] = f;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -T(1);
    result[3][2] = -(T(2) * zFar * zNear) / (zFar - zNear);

    return result;
}

#endif