#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class health_component : public mngn::custom_component, public mngn::subject
    {
    public:
        health_component()           = default;
        explicit health_component(int health) : health_{health}, original_health_{health} {}
        ~health_component() override = default;
        
        health_component(health_component const &other)            = delete;
        health_component(health_component &&other)                 = delete;
        health_component &operator=(health_component const &other) = delete;
        health_component &operator=(health_component &&other)      = delete;

        virtual void take_damage(int damage);
        virtual void heal(int health);
        [[nodiscard]] virtual auto health() const -> int { return health_;}
        
    protected:
        int health_ = 0;
        int const original_health_ = 0;
    };
}
