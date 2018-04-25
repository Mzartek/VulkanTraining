#include <private/Camera.h>

namespace VT
{
Camera::Camera()
{
}

void Camera::SetPerspective(float fov, float width, float height, float near, float far)
{
    m_projectionMatrix = glm::perspectiveFov(fov, width, height, near, far);
}
}
