#pragma once

// Project includes
#include "state/player_state.h"

namespace qbert
{
    class swearing_state final : public player_state
    {
    public:
        explicit swearing_state(mngn::game_object* player_ptr);
    };
}
