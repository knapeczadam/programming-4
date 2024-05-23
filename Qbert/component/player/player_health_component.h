#pragma once

// Project includes
#include "component/character/health_component.h"

namespace qbert
{
    class player_health_component final : public health_component
    {
    public:
        player_health_component()           = default;
        explicit player_health_component(int health);
        ~player_health_component() override = default;

        player_health_component(player_health_component const &other)            = delete;
        player_health_component(player_health_component &&other)                 = delete;
        player_health_component &operator=(player_health_component const &other) = delete;
        player_health_component &operator=(player_health_component &&other)      = delete;

        void on_enable() override;

        void take_damage(int damage) override;
        void heal(int health) override;
        [[nodiscard]] auto health() const -> int override;
    };
}
