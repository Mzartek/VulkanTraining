#ifndef VT_ORTHOGRAPHIC_CAMERA_INCLUDE_H
#define VT_ORTHOGRAPHIC_CAMERA_INCLUDE_H

#include "Camera.h"

namespace VT
{
class LIB_INTERFACE OrthographicCamera : public Camera
{
public:
    OrthographicCamera();

    void SetLeft(float value);
    void SetRight(float value);
    void SetBottom(float value);
    void SetTop(float value);
    void SetNear(float value);
    void SetFar(float value);

    float GetLeft() const;
    float GetRight() const;
    float GetBottom() const;
    float GetTop() const;
    float GetNear() const;
    float GetFar() const;

private:
    float _left;
    float _right;
    float _bottom;
    float _top;
    float _near;
    float _far;
};
}

#endif
