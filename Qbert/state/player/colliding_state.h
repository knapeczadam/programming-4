#pragma once

// Project includes
#include "state/player/player_state.h"

namespace qbert
{
    class colliding_state final : public player_state
    {
    public:
        explicit colliding_state(mngn::game_object* player_ptr);

        void on_enter() override;
    };
}
