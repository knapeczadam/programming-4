#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class single_state final : public game_state
    {
    public:
        explicit single_state(game_state_component *game_state_comp_ptr);
        ~single_state() override = default;

        single_state(single_state const &other)            = delete;
        single_state(single_state &&other)                 = delete;
        single_state &operator=(single_state const &other) = delete;
        single_state &operator=(single_state &&other)      = delete;

        void on_enter() override;
    };
}
