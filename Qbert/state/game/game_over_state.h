#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class game_over_state final : public game_state
    {
    public:
        game_over_state();
        ~game_over_state() override = default;

        game_over_state(game_over_state const &other)            = delete;
        game_over_state(game_over_state &&other)                 = delete;
        game_over_state &operator=(game_over_state const &other) = delete;
        game_over_state &operator=(game_over_state &&other)      = delete;

        void on_enter() override;
        void on_exit() override;
    };
}
