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

        void enable_cube_animations();
        void disable_cube_animations();

    private:
        float accu_time_      = 0.0f;
        float loading_time_   = 3.0f;
        float disk_time_      = 0.0f;
        float disappear_time_ = 0.5f;
        
        float const bonus_time_   = 2.08f;
        float const time_per_disk_ = 0.5f;
        
        int disk_count_     = 1;
        bool bonus_given_   = false;
    };
}
