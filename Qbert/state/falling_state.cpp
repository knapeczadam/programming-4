#include "falling_state.h"

// Project includes
#include "component/player/fall_component.h"
#include "component/player/position_idx_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    falling_state::falling_state(mngn::game_object *player_ptr, int col_idx)
        : player_state(player_ptr)
        , col_idx_{col_idx}
    {
    }

    void falling_state::on_enter()
    {
        auto fall_comp_ptr = player_ptr_->component<fall_component>();
        fall_comp_ptr->fall(col_idx_);
    }
}
