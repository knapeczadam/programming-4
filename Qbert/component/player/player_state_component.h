#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Standard includes
#include <memory>

#include "state/player_state.h"

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

        template <class T, typename... Args>
        void change_state(Args &&...args);

        template <class T>
        [[nodiscard]] auto get_state() const -> T *;

        template <class T>
        [[nodiscard]] auto is_state() const -> bool;

    private:
        std::unique_ptr<player_state> player_state_;
    };
}

#include "player_state_component.hpp"
