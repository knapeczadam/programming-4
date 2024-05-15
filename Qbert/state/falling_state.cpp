#include "falling_state.h"

// Project includes
#include "component/player/fall_component.h"
#include "component/player/health_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    falling_state::falling_state(mngn::game_object *player_ptr, int row_dir, int col_dir, int row_idx, int col_idx)
        : player_state(player_ptr)
        , row_dir_{row_dir}
        , col_dir_{col_dir}
        , row_idx_{row_idx}
        , col_idx_{col_idx}
    {
    }

    void falling_state::on_enter()
    {
        player_ptr_->component<fall_component>()->fall(row_dir_, col_dir_, row_idx_, col_idx_);
    }
}
