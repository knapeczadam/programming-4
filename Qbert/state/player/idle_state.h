#pragma once

// Project includes
#include "state/player/player_state.h"

namespace qbert
{
    class idle_state final : public player_state
    {
    public:
        explicit idle_state(mngn::game_object* player_ptr);

        void on_enter() override;
    };
}
