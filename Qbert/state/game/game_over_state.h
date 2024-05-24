#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class game_over_state final : public game_state
    {
    public:
        explicit game_over_state(game_state_component *game_state_comp_ptr);
        ~game_over_state() override = default;

        game_over_state(game_over_state const &other)            = delete;
        game_over_state(game_over_state &&other)                 = delete;
        game_over_state &operator=(game_over_state const &other) = delete;
        game_over_state &operator=(game_over_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        float game_over_time_ = 5.0f;
        float accu_time_      = 0.0f;
    };
}
