#ifndef VT_POSITION_INCLUDE_H
#define VT_POSITION_INCLUDE_H

#include "Export.h"

namespace VT
{
class LIB_INTERFACE Position
{
public:
    Position();

    void SetLocationX(float value);
    void SetLocationY(float value);
    void SetLocationZ(float value);

    void SetRotationX(float value);
    void SetRotationY(float value);
    void SetRotationZ(float value);

    void SetScaleX(float value);
    void SetScaleY(float value);
    void SetScaleZ(float value);

    float GetLocationX() const;
    float GetLocationY() const;
    float GetLocationZ() const;

    float GetRotationX() const;
    float GetRotationY() const;
    float GetRotationZ() const;

    float GetScaleX() const;
    float GetScaleY() const;
    float GetScaleZ() const;

private:
    float _locationX;
    float _locationY;
    float _locationZ;

    float _rotationX;
    float _rotationY;
    float _rotationZ;

    float _scaleX;
    float _scaleY;
    float _scaleZ;
};
}

#endif
