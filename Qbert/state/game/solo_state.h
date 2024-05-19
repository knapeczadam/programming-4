#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class solo_state final : public game_state
    {
    public:
        explicit solo_state(game_state_component *game_state_comp_ptr);
        ~solo_state() override = default;

        solo_state(solo_state const &other)            = delete;
        solo_state(solo_state &&other)                 = delete;
        solo_state &operator=(solo_state const &other) = delete;
        solo_state &operator=(solo_state &&other)      = delete;

        void on_enter() override;
    };
}
