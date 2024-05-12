#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Standard includes
#include <memory>

namespace qbert
{
    // Forward declarations
    class player_state;
    
    class player_state_component final : public mngn::custom_component
    {
    public:
        player_state_component();
        ~player_state_component() override;

        player_state_component(player_state_component const &other)            = delete;
        player_state_component(player_state_component &&other)                 = delete;
        player_state_component &operator=(player_state_component const &other) = delete;
        player_state_component &operator=(player_state_component &&other)      = delete;

        void awake() override;
        void update() override;
        void change_state(std::unique_ptr<player_state> new_state);
        [[nodiscard]] auto get_state() const -> player_state * { return player_state_.get(); }

    private:
        std::unique_ptr<player_state> player_state_;
    };
}
