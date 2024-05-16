#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class waiting_state final : public character_state
    {
    public:
        explicit waiting_state(mngn::game_object* character_ptr, float waiting_time);

        void update() override;
        void on_exit() override;

    private:
        float waiting_time_ = 0.0f;
        float accu_time_    = 0.0f;
    };
}
