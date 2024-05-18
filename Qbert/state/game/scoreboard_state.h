#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class scoreboard_state final : public game_state
    {
    public:
        scoreboard_state() = default;
        ~scoreboard_state() override = default;

        scoreboard_state(scoreboard_state const &other)            = delete;
        scoreboard_state(scoreboard_state &&other)                 = delete;
        scoreboard_state &operator=(scoreboard_state const &other) = delete;
        scoreboard_state &operator=(scoreboard_state &&other)      = delete;
    };
}
