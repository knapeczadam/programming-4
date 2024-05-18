#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class versus_state final : public game_state
    {
    public:
        versus_state() = default;
        ~versus_state() override = default;

        versus_state(versus_state const &other)            = delete;
        versus_state(versus_state &&other)                 = delete;
        versus_state &operator=(versus_state const &other) = delete;
        versus_state &operator=(versus_state &&other)      = delete;
    };
}
