#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "component/state/i_state_component.h"

namespace qbert
{
    class player_state_component final : public mngn::custom_component, public i_state_component
    {
    public:
        player_state_component();
        ~player_state_component() override = default;

        player_state_component(player_state_component const &other)            = delete;
        player_state_component(player_state_component &&other)                 = delete;
        player_state_component &operator=(player_state_component const &other) = delete;
        player_state_component &operator=(player_state_component &&other)      = delete;

        void awake() override;
        void update() override;
    };
}
