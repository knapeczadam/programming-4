#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class input_state final : public game_state
    {
    public:
        explicit input_state(game_state_component *game_state_comp_ptr);
        ~input_state() override = default;

        input_state(input_state const &other)            = delete;
        input_state(input_state &&other)                 = delete;
        input_state &operator=(input_state const &other) = delete;
        input_state &operator=(input_state &&other)      = delete;

        void on_enter() override;
        void update()   override;
        void on_exit()  override;

    private:
        float input_time_                = 30.0f;
        float const original_input_time_ = 30.0f;
        int countdown_                   = 30;
        int const original_countdown_    = 30;
        float accu_time_                 = 1.0f;
    };
}
