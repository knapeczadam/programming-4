#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class npc_start_state final : public character_state
    {
    public:
        explicit npc_start_state(mngn::game_object* character_ptr);

        void on_enter() override;
    };
}
