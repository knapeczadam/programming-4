#pragma once

// Project includes
#include "state/player_state.h"

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class jumping_state final : public player_state
    {
    public:
        jumping_state(mngn::game_object* player_ptr, int row_dir, int col_dir);

        void on_enter() override;

    private:
        int row_dir_ = 0;
        int col_dir_ = 0;
    };
}
