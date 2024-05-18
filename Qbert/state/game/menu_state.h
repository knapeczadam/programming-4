#pragma once

// Project includes
#include "state/game/game_state.h"

namespace qbert
{
    class menu_state final : public game_state
    {
    public:
        menu_state();
        ~menu_state() override = default;

        menu_state(menu_state const &other)            = delete;
        menu_state(menu_state &&other)                 = delete;
        menu_state &operator=(menu_state const &other) = delete;
        menu_state &operator=(menu_state &&other)      = delete;

        void on_enter() override;
        void on_exit() override;
    };
}
