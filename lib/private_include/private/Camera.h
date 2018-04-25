#ifndef VT_CAMERA_INCLUDE_H
#define VT_CAMERA_INCLUDE_H

#include "Externals.h"

namespace VT
{
class Camera
{
public:
    Camera();

    void SetPerspective(float fov, float width, float height, float near, float far);

private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
};
}

#endif
