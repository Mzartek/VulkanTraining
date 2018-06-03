#include <VulkanTraining/Cameras/PerspectiveCamera.h>

namespace VT
{
PerspectiveCamera::PerspectiveCamera()
    : _fov(0.0f)
    , _width(0.0f)
    , _height(0.0f)
    , _near(0.0f)
    , _far(0.0f)
{
}

void PerspectiveCamera::SetFOV(float value)
{
    _fov = value;
}

void PerspectiveCamera::SetWidth(float value)
{
    _width = value;
}

void PerspectiveCamera::SetHeight(float value)
{
    _height = value;
}

void PerspectiveCamera::SetNear(float value)
{
    _near = value;
}

void PerspectiveCamera::SetFar(float value)
{
    _far = value;
}

float PerspectiveCamera::GetFOV() const
{
    return _fov;
}

float PerspectiveCamera::GetWidth() const
{
    return _width;
}

float PerspectiveCamera::GetHeight() const
{
    return _height;
}

float PerspectiveCamera::GetNear() const
{
    return _near;
}

float PerspectiveCamera::GetFar() const
{
    return _far;
}
}
