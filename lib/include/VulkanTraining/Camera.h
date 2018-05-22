#ifndef VT_CAMERA_INCLUDE_H
#define VT_CAMERA_INCLUDE_H

#include "Export.h"

namespace VT
{
class LIB_INTERFACE Camera
{
public:
    Camera();

    void SetEyeX(float value);
    void SetEyeY(float value);
    void SetEyeZ(float value);

    void SetCenterX(float value);
    void SetCenterY(float value);
    void SetCenterZ(float value);

    void SetUpX(float value);
    void SetUpY(float value);
    void SetUpZ(float value);

    float GetEyeX() const;
    float GetEyeY() const;
    float GetEyeZ() const;

    float GetCenterX() const;
    float GetCenterY() const;
    float GetCenterZ() const;

    float GetUpX() const;
    float GetUpY() const;
    float GetUpZ() const;

private:
    float _eyeX;
    float _eyeY;
    float _eyeZ;

    float _centerX;
    float _centerY;
    float _centerZ;

    float _upX;
    float _upY;
    float _upZ;
};
}

#endif
