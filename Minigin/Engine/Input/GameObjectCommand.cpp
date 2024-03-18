#include "GameObjectCommand.h"

#include "BaseComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"

namespace dae
{
    void MoveLeftCommand::Execute()
    {
        if (GetGameObject()->HasComponent(ComponentType::Movement))
        {
            const auto movementComponent = GetGameObject()->GetComponent(ComponentType::Movement);
            if (movementComponent.has_value())
            {
                const auto move = static_cast<MovementComponent*>(movementComponent.value());
                move->MoveLeft();
            }
        }
    }

    void MoveRightCommand::Execute()
    {
        if (GetGameObject()->HasComponent(ComponentType::Movement))
        {
            const auto movementComponent = GetGameObject()->GetComponent(ComponentType::Movement);
            if (movementComponent.has_value())
            {
                const auto move = static_cast<MovementComponent*>(movementComponent.value());
                move->MoveRight();
            }
        }
    }

    void MoveUpCommand::Execute()
    {
        if (GetGameObject()->HasComponent(ComponentType::Movement))
        {
            const auto movementComponent = GetGameObject()->GetComponent(ComponentType::Movement);
            if (movementComponent.has_value())
            {
                const auto move = static_cast<MovementComponent*>(movementComponent.value());
                move->MoveUp();
            }
        }
    }

    void MoveDownCommand::Execute()
    {
        if (GetGameObject()->HasComponent(ComponentType::Movement))
        {
            const auto movementComponent = GetGameObject()->GetComponent(ComponentType::Movement);
            if (movementComponent.has_value())
            {
                const auto move = static_cast<MovementComponent*>(movementComponent.value());
                move->MoveDown();
            }
        }
    }
}
