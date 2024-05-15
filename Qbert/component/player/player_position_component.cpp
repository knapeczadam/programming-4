#include "player_position_component.h"

// Project includes
#include "component/player/jump_component.h"
#include "component/direction_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    player_position_component::player_position_component(int row_idx, int col_idx)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
    {
    }

    void player_position_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void player_position_component::update_position()
    {
        row_idx_ += direction_comp_ptr_->row();
        col_idx_ += direction_comp_ptr_->col();
        notify_observers("position_changed");
    }
}
