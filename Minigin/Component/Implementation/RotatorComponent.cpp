#include "RotatorComponent.h"

// Project includes
#include "GameObject.h"

namespace dae
{
    void RotatorComponent::Update()
    {
        const auto& pos = GetOwner()->GetLocalPosition();
        const float cosAngle = glm::cos(glm::radians(m_rotationAngleDeg));
        const float sinAngle = glm::sin(glm::radians(m_rotationAngleDeg));
        const float newX = pos.x * cosAngle - pos.y * sinAngle;
        const float newY = pos.x * sinAngle + pos.y * cosAngle;
        GetOwner()->SetLocalPosition(newX, newY);
        // TODO: delta time?
    }
}
