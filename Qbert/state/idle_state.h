#pragma once

// Project includes
#include "state/player_state.h"

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class idle_state final : public player_state
    {
    public:
        explicit idle_state(mngn::game_object* player_ptr);
    };
}
