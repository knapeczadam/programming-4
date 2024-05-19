#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class scoreboard_state final : public game_state
    {
    public:
        explicit scoreboard_state(game_state_component *game_state_comp_ptr);
        ~scoreboard_state() override = default;

        scoreboard_state(scoreboard_state const &other)            = delete;
        scoreboard_state(scoreboard_state &&other)                 = delete;
        scoreboard_state &operator=(scoreboard_state const &other) = delete;
        scoreboard_state &operator=(scoreboard_state &&other)      = delete;

        void on_enter() override;
        void on_exit() override;
    };
}
