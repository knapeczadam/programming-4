#include "Transform.h"

namespace dae
{
    void Transform::SetWorldPosition(const float x, const float y)
    {
        SetWorldPosition(glm::vec3{ x, y, m_worldPosition.z });
    }

    void Transform::SetWorldPosition(const float x, const float y, const float z)
    {
        SetWorldPosition(glm::vec3{ x, y, z });
    }

    void Transform::SetWorldPosition(const glm::vec2& position)
    {
        SetWorldPosition(glm::vec3{ position, m_worldPosition.z });
    }

    void Transform::SetWorldPosition(const glm::vec3& position)
    {
        m_worldPosition = position;
    }

    void Transform::SetLocalPosition(const float x, const float y)
    {
        SetLocalPosition(glm::vec3{ x, y, m_localPosition.z });
    }

    void Transform::SetLocalPosition(const float x, const float y, const float z)
    {
        SetLocalPosition(glm::vec3{ x, y, z });
    }

    void Transform::SetLocalPosition(const glm::vec2& position)
    {
        SetLocalPosition(glm::vec3{ position, m_localPosition.z });
    }

    void Transform::SetLocalPosition(const glm::vec3& position)
    {
        m_localPosition = position;
    }
}
