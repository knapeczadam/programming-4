#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class round_loading_state final : public game_state
    {
    public:
        explicit round_loading_state(game_state_component *game_state_comp_ptr);
        ~round_loading_state() override = default;

        round_loading_state(round_loading_state const &other)            = delete;
        round_loading_state(round_loading_state &&other)                 = delete;
        round_loading_state &operator=(round_loading_state const &other) = delete;
        round_loading_state &operator=(round_loading_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        float loading_time_ = 5.0f;
        float bonus_time_   = 3.5f;
        float accu_time_    = 0.0f;
        bool bonus_given_   = false;
    };
}
