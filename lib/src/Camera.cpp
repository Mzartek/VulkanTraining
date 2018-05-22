#include <VulkanTraining/Camera.h>

namespace VT
{
Camera::Camera()
    : _eyeX(0.0f)
    , _eyeY(0.0f)
    , _eyeZ(0.0f)
    , _centerX(0.0f)
    , _centerY(0.0f)
    , _centerZ(0.0f)
    , _upX(0.0f)
    , _upY(0.0f)
    , _upZ(0.0f)
{
}

void Camera::SetEyeX(float value)
{
    _eyeX = value;
}

void Camera::SetEyeY(float value)
{
    _eyeY = value;
}

void Camera::SetEyeZ(float value)
{
    _eyeZ = value;
}

void Camera::SetCenterX(float value)
{
    _centerX = value;
}

void Camera::SetCenterY(float value)
{
    _centerY = value;
}

void Camera::SetCenterZ(float value)
{
    _centerZ = value;
}

void Camera::SetUpX(float value)
{
    _upX = value;
}

void Camera::SetUpY(float value)
{
    _upY = value;
}

void Camera::SetUpZ(float value)
{
    _upZ = value;
}

float Camera::GetEyeX() const
{
    return _eyeX;
}

float Camera::GetEyeY() const
{
    return _eyeY;
}

float Camera::GetEyeZ() const
{
    return _eyeZ;
}

float Camera::GetCenterX() const
{
    return _centerX;
}

float Camera::GetCenterY() const
{
    return _centerY;
}

float Camera::GetCenterZ() const
{
    return _centerZ;
}

float Camera::GetUpX() const
{
    return _upX;
}

float Camera::GetUpY() const
{
    return _upY;
}

float Camera::GetUpZ() const
{
    return _upZ;
}
}
