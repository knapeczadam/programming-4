#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class loading_state final : public game_state
    {
    public:
        loading_state() = default;
        ~loading_state() override = default;

        loading_state(loading_state const &other)            = delete;
        loading_state(loading_state &&other)                 = delete;
        loading_state &operator=(loading_state const &other) = delete;
        loading_state &operator=(loading_state &&other)      = delete;
    };
}
