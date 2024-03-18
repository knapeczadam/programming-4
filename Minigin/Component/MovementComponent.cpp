#include "MovementComponent.h"

#include "GameObject.h"

namespace dae
{
    void MovementComponent::MoveLeft()
    {
        const auto oldPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(oldPos.x - m_Speed, oldPos.y);
    }

    void MovementComponent::MoveRight()
    {
        const auto oldPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(oldPos.x + m_Speed, oldPos.y);
    }

    void MovementComponent::MoveUp()
    {
        const auto oldPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(oldPos.x, oldPos.y - m_Speed);
    }

    void MovementComponent::MoveDown()
    {
        const auto oldPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(oldPos.x, oldPos.y + m_Speed);
    }
}
