#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class swearing_state final : public character_state
    {
    public:
        explicit swearing_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void update() override;
        void on_exit() override;
        
    private:
        float             swear_time_       = 2.0f;
        float             accu_time_        = 0.0f;
        bool              is_swearing_      = false;
    };
}
