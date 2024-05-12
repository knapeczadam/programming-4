﻿#pragma once

// Project includes
#include "player_state.h"

namespace qbert
{
    class waiting_state final : public player_state
    {
    public:
        explicit waiting_state(mngn::game_object* player_ptr);

        void update() override;
        void on_exit() override;

    private:
        float waiting_time = 2.0f;
        float accu_time    = 0.0f;
    };
}
