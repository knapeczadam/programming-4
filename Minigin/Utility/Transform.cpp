#include "Transform.h"

namespace dae
{
    void Transform::SetPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
    }

    void Transform::SetPosition(const float x, const float y, const float z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;
    }

    void Transform::SetPosition(const glm::vec2& position)
    {
        m_position.x = position.x;
        m_position.y = position.y;
    }

    void Transform::SetPosition(const glm::vec3& position)
    {
        m_position = position;
    }
}
