#pragma once

// Project includes
#include "state/player/player_state.h"

namespace qbert
{
    class jumping_state final : public player_state
    {
    public:
        jumping_state(mngn::game_object* player_ptr);

        void on_enter() override;
    };
}
