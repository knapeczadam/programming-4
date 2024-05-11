#include "position_component.h"

// Project includes
#include "component/animation/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void position_component::set_position(int row, int col)
    {
        curr_row_ += row;
        curr_col_ += col;
        
        notify_observers("position_changed");
    }

    void position_component::notify(std::string const &event, subject *subject_ptr)
    {
        if (event == "jump_finished")
        {
            auto jump_comp_ptr = dynamic_cast<jump_component*>(subject_ptr);
            set_position(jump_comp_ptr->get_row(), jump_comp_ptr->get_col());
        }
    }
}
