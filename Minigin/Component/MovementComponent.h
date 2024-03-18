#pragma once
#include "PhysicsComponent.h"

namespace dae
{
    class MovementComponent : public PhysicsComponent
    {
    public:
        MovementComponent() = default;
        virtual ~MovementComponent() override = default;

        MovementComponent(const MovementComponent& other)            = delete;
        MovementComponent(MovementComponent&& other)                 = delete;
        MovementComponent& operator=(const MovementComponent& other) = delete;
        MovementComponent& operator=(MovementComponent&& other)      = delete;

        ComponentType GetType() const override { return ComponentType::Movement; }
        void SetSpeed(float speed) { m_Speed = speed; }

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();

    private:
        float m_Speed{ 1.0f };
    };
}
