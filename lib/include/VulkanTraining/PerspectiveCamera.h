#ifndef VT_PERSPECTIVE_CAMERA_INCLUDE_H
#define VT_PERSPECTIVE_CAMERA_INCLUDE_H

#include "Camera.h"

namespace VT
{
class LIB_INTERFACE PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera();

    void SetFOV(float value);
    void SetWidth(float value);
    void SetHeight(float value);
    void SetNear(float value);
    void SetFar(float value);

    float GetFOV() const;
    float GetWidth() const;
    float GetHeight() const;
    float GetNear() const;
    float GetFar() const;

private:
    float _fov;
    float _width;
    float _height;
    float _near;
    float _far;
};
}

#endif
