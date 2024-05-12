#pragma once

// Project includes
#include "state/player_state.h"

namespace qbert
{
    class falling_state final : public player_state
    {
    public:
        explicit falling_state(mngn::game_object* player_ptr, int col_idx);

        void on_enter() override;

    private:
        int col_idx_ = 0;
    };
}
