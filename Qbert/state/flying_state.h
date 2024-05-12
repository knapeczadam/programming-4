#pragma once

// Project includes
#include "state/player_state.h"

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class flying_state final : public player_state
    {
    public:
        explicit flying_state(mngn::game_object* player_ptr);
    };
}
