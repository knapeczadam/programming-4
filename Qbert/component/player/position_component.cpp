#include "position_component.h"

// Project includes
#include "component/player/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void position_component::set_position(int row_dir, int col_dir)
    {
        row_pos_ += row_dir;
        col_pos_ += col_dir;
        
        notify_observers("position_changed");
    }
}
