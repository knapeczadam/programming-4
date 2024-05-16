#include "position_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void position_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void position_component::update_position()
    {
        row_idx_ += direction_comp_ptr_->row();
        col_idx_ += direction_comp_ptr_->col();
        notify_observers("position_changed");
    }

    void position_component::reset(int row_idx, int col_idx)
    {
        row_idx_ = row_idx;
        col_idx_ = col_idx;
    }
}
