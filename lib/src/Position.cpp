#include <VulkanTraining/Position.h>

namespace VT
{
Position::Position()
    : _locationX(0.0f)
    , _locationY(0.0f)
    , _locationZ(0.0f)
    , _rotationX(0.0f)
    , _rotationY(0.0f)
    , _rotationZ(0.0f)
    , _scaleX(0.0f)
    , _scaleY(0.0f)
    , _scaleZ(0.0f)
{
}

void Position::SetLocationX(float value)
{
    _locationX = value;
}

void Position::SetLocationY(float value)
{
    _locationY = value;
}

void Position::SetLocationZ(float value)
{
    _locationZ = value;
}

void Position::SetRotationX(float value)
{
    _rotationX = value;
}

void Position::SetRotationY(float value)
{
    _rotationY = value;
}

void Position::SetRotationZ(float value)
{
    _rotationZ = value;
}

void Position::SetScaleX(float value)
{
    _scaleX = value;
}

void Position::SetScaleY(float value)
{
    _scaleY = value;
}

void Position::SetScaleZ(float value)
{
    _scaleZ = value;
}

float Position::GetLocationX() const
{
    return _locationX;
}

float Position::GetLocationY() const
{
    return _locationY;
}

float Position::GetLocationZ() const
{
    return _locationZ;
}

float Position::GetRotationX() const
{
    return _rotationX;
}

float Position::GetRotationY() const
{
    return _rotationY;
}

float Position::GetRotationZ() const
{
    return _rotationZ;
}

float Position::GetScaleX() const
{
    return _scaleX;
}

float Position::GetScaleY() const
{
    return _scaleY;
}

float Position::GetScaleZ() const
{
    return _scaleZ;
}
}
