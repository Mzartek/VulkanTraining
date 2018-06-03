#include <private/Transform.h>

namespace VT
{
Transform::Transform(Device& device)
    : m_matricesBuffer(device, BufferType::Uniform, sizeof(m_matrices))
{
}

void Transform::SetPerspectiveProjection(float fov, float width, float height, float near, float far)
{
    m_matrices.projection = glm::perspectiveFov(fov, width, height, near, far);
}

void Transform::SetOrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
    m_matrices.projection = glm::ortho(left, right, bottom, top, near, far);
}

void Transform::SetView(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
    m_matrices.view = glm::lookAt(eye, center, up);
}

void Transform::SetModel(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
    m_matrices.model = glm::translate(glm::mat4(1.0f), translation) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), scale);
}

void Transform::SetModel(const glm::vec3& translation, const glm::quat& rotation, const glm::vec3& scale)
{
    m_matrices.model = glm::translate(glm::mat4(1.0f), translation) *
        glm::toMat4(rotation) *
        glm::scale(glm::mat4(1.0f), scale);
}

const Buffer& Transform::GetMatricesBuffer() const
{
    return m_matricesBuffer;
}

void Transform::UpdateMatricesBuffer()
{
    m_matricesBuffer.UpdateData(&m_matrices);
}
}
