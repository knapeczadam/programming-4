﻿#pragma once

// Project includes
#include "state/player/player_state.h"

namespace qbert
{
    class dead_state final : public player_state
    {
    public:
        explicit dead_state(mngn::game_object* player_ptr);
    };
}