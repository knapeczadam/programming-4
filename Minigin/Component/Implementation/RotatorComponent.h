#pragma once

// Project includes
#include "PhysicsComponent.h"

namespace dae
{
    class RotatorComponent final : public PhysicsComponent
    {
    public:
        RotatorComponent() = default;
        virtual ~RotatorComponent() override = default;

        RotatorComponent(const RotatorComponent& other) = delete;
        RotatorComponent(RotatorComponent&& other) = delete;
        RotatorComponent& operator=(const RotatorComponent& other) = delete;
        RotatorComponent& operator=(RotatorComponent&& other) = delete;

        ComponentType GetType() const override { return ComponentType::Rotator; }

        void Update() override;

    private:
        const float m_rotationAngleDeg = 1.0f;
        
    };
}
