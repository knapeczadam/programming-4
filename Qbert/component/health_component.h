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
        ~health_component() override = default;
        
        health_component(health_component const &other)            = delete;
        health_component(health_component &&other)                 = delete;
        health_component &operator=(health_component const &other) = delete;
        health_component &operator=(health_component &&other)      = delete;

        void awake() override;

        void take_damage(int damage);
        [[nodiscard]] auto get_health() const -> int { return health_; }

    private:
        int health_ = 3;
    };
}
