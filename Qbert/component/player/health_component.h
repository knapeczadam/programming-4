#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class health_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        health_component()           = default;
        explicit health_component(int health);
        ~health_component() override = default;
        
        health_component(health_component const &other)            = delete;
        health_component(health_component &&other)                 = delete;
        health_component &operator=(health_component const &other) = delete;
        health_component &operator=(health_component &&other)      = delete;

        void on_enable() override;
        void on_disable() override;

        void take_damage(int damage);
        void heal(int health);
        [[nodiscard]] auto health() const -> int { return health_; }

    private:
        int health_ = 0;
        int const original_health_ = 0;
    };
}
