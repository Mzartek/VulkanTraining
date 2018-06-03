#include <VulkanTraining/OrthographicCamera.h>

namespace VT
{
OrthographicCamera::OrthographicCamera()
    : _left(0.0f)
    , _right(0.0f)
    , _bottom(0.0f)
    , _top(0.0f)
    , _near(0.0f)
    , _far(0.0f)
{
}

void OrthographicCamera::SetLeft(float value)
{
    _left = value;
}

void OrthographicCamera::SetRight(float value)
{
    _right = value;
}

void OrthographicCamera::SetBottom(float value)
{
    _bottom = value;
}

void OrthographicCamera::SetTop(float value)
{
    _top = value;
}

void OrthographicCamera::SetNear(float value)
{
    _near = value;
}

void OrthographicCamera::SetFar(float value)
{
    _far = value;
}

float OrthographicCamera::GetLeft() const
{
    return _left;
}

float OrthographicCamera::GetRight() const
{
    return _right;
}

float OrthographicCamera::GetBottom() const
{
    return _bottom;
}

float OrthographicCamera::GetTop() const
{
    return _top;
}

float OrthographicCamera::GetNear() const
{
    return _near;
}

float OrthographicCamera::GetFar() const
{
    return _far;
}
}
