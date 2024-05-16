#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class npc_dead_state final : public character_state
    {
    public:
        explicit npc_dead_state(mngn::game_object* character_ptr);

        void update() override;
        void on_exit() override;

    private:
        float dead_time_ = 2.0f;
        float accu_time_ = 0.0f;
    };
}
