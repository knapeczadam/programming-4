#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class npc_idle_state final : public character_state
    {
    public:
        explicit npc_idle_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void update() override;

    private:
        float idle_time_ = 1.0f;
        float accu_time_ = 0.0f;
    };

}
