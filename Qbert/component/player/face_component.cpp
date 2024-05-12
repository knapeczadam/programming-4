#include "face_component.h"

// Proejct includes
#include "jump_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void face_component::awake()
    {
        sprite_comp_ptr_ = get_owner()->get_component<mngn::sprite_component>();
    }

    void face_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "jump_finished")
        {
            auto jump_comp_ptr = dynamic_cast<jump_component*>(subject_ptr);
            auto row = jump_comp_ptr->get_row_direction();
            auto col = jump_comp_ptr->get_col_direction();
            if (row == -1 and col == 0)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(0);
            }
            else if (row == -1 and col == -1)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(2);
            }
            else if (row == 1 and col == 0)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(6);
            }
            else
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(4);
            }
        }
        if (event == "jump_started")
        {
            auto jump_comp_ptr = dynamic_cast<jump_component*>(subject_ptr);
            auto row = jump_comp_ptr->get_row_direction();
            auto col = jump_comp_ptr->get_col_direction();
            if (row == -1 and col == 0)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(1);
            }
            else if (row == -1 and col == -1)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(3);
            }
            else if (row == 1 and col == 0)
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(7);
            }
            else
            {
                sprite_comp_ptr_->get_sprite()->set_current_frame(5);
            }
        }
    }
}
