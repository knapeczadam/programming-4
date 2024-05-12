#pragma once

// Project includes
#include "state/player_state.h"

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class null_state final : public player_state
    {
    public:
        explicit null_state(mngn::game_object* player_ptr);
    };
}
