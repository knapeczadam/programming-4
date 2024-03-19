#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class PhysicsComponent : public BaseComponent
    {
    public:
        PhysicsComponent() = default;
        virtual ~PhysicsComponent() override = default;

        PhysicsComponent(const PhysicsComponent& other)            = delete;
        PhysicsComponent(PhysicsComponent&& other)                 = delete;
        PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
        PhysicsComponent& operator=(PhysicsComponent&& other)      = delete;
        
        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Physics; }
    };
}
