#ifndef VT_TRANSFORM_INCLUDE_H
#define VT_TRANSFORM_INCLUDE_H

#include "Externals.h"

#include "Buffer.h"

namespace VT
{
class Transform
{
public:
    struct Matrices
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };

    Transform(Device& device);

    void SetPerspectiveProjection(float fov, float width, float height, float near, float far);
    void SetOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);

    void SetView(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);

    void SetModel(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
    void SetModel(const glm::vec3& translation, const glm::quat& rotation, const glm::vec3& scale);

    const Buffer& GetMatricesBuffer() const;

    void UpdateMatricesBuffer();

private:
    Matrices m_matrices;
    Buffer m_matricesBuffer;
};
}

#endif
