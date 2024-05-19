#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class loading_state final : public game_state
    {
    public:
        loading_state(game_state_component *game_state_comp_ptr, int game_mode);
        ~loading_state() override = default;

        loading_state(loading_state const &other)            = delete;
        loading_state(loading_state &&other)                 = delete;
        loading_state &operator=(loading_state const &other) = delete;
        loading_state &operator=(loading_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        void load_game_mode();

    private:
        int game_mode_ = 0;
        float loading_time_ = 5.0f;
        float accu_time_    = 0.0f;
    };
}
