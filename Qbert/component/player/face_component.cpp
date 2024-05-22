#include "face_component.h"

// Proejct includes
#include "component/character/direction_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void face_component::awake()
    {
        sprite_comp_ptr_ = owner()->component<mngn::sprite_component>();
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void face_component::on_enable()
    {
        sprite_comp_ptr_ = owner()->component<mngn::sprite_component>();
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void face_component::set_sprite_orientation(int left_dir_frame, int right_dir_frame, int up_dir_frame, int down_dir_frame, int diagonal_dir_frame)
    {
        int row_dir = direction_comp_ptr_->row();
        int col_dir = direction_comp_ptr_->col();
        
        if (row_dir == -1 and col_dir == -1)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(left_dir_frame);
        }
        else if (row_dir == 1 and col_dir == 1)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(right_dir_frame);
        }
        else if (row_dir == -1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(up_dir_frame);
        }
        else if (row_dir == 1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(down_dir_frame);
        }
        else
        {
            sprite_comp_ptr_->sprite()->set_current_frame(diagonal_dir_frame);
        }
    }
}
