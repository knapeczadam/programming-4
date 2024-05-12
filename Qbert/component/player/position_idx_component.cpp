#include "position_idx_component.h"

// Project includes
#include "component/player/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    position_idx_component::position_idx_component(int row_idx, int col_idx)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
    {
    }

    void position_idx_component::set_position_idx(int row_dir, int col_dir)
    {
        row_idx_ += row_dir;
        col_idx_ += col_dir;
        notify_observers("position_changed");
    }
}
