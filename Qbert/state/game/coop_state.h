#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class coop_state final : public game_state
    {
    public:
        explicit coop_state(game_state_component *game_state_comp_ptr);
        ~coop_state() override = default;

        coop_state(coop_state const &other)            = delete;
        coop_state(coop_state &&other)                 = delete;
        coop_state &operator=(coop_state const &other) = delete;
        coop_state &operator=(coop_state &&other)      = delete;

        void on_enter() override;
    };
}
