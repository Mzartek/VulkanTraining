#ifndef VT_CAMERA_INCLUDE_H
#define VT_CAMERA_INCLUDE_H

#include "Externals.h"

namespace VT
{
class Camera
{
public:
    Camera();

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
}

#endif
