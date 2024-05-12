#pragma once

// Project includes
#include "state/player_state.h"

namespace qbert
{
    class landing_state final : public player_state
    {
    public:
        explicit landing_state(mngn::game_object* player_ptr);

        void on_enter() override;
    };
}
