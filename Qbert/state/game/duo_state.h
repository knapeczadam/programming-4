#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class duo_state final : public game_state
    {
    public:
        duo_state();
        ~duo_state() override = default;

        duo_state(duo_state const &other)            = delete;
        duo_state(duo_state &&other)                 = delete;
        duo_state &operator=(duo_state const &other) = delete;
        duo_state &operator=(duo_state &&other)      = delete;

        void on_enter() override;
        void on_exit() override;
    };
}
