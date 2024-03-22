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

        // TODO: do we really need FixedUpdate?
        // virtual void FixedUpdate() = 0;
        
        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Physics; }
    };
}
