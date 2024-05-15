#pragma once

// Project includes
#include "state/player/player_state.h"

namespace qbert
{
    class falling_state final : public player_state
    {
    public:
        explicit falling_state(mngn::game_object* player_ptr, int row_dir, int col_dir, int row_idx, int col_idx);

        void on_enter() override;

    private:
        int row_dir_ = 0;
        int col_dir_ = 0;
        int row_idx_ = 0;
        int col_idx_ = 0;
    };
}
