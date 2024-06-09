#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class versus_state final : public game_state
    {
    public:
        explicit versus_state(game_state_component *game_state_comp_ptr);
        ~versus_state() override = default;

        versus_state(versus_state const &other)            = delete;
        versus_state(versus_state &&other)                 = delete;
        versus_state &operator=(versus_state const &other) = delete;
        versus_state &operator=(versus_state &&other)      = delete;

        void on_enter() override;
    };
}
