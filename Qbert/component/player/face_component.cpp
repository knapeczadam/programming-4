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
        sprite_comp_ptr_ = owner()->component<mngn::sprite_component>();
    }
    
    void face_component::set_jump_sprite(int row_dir, int col_dir)
    {
        if (row_dir == -1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(1);
        }
        else if (row_dir == -1 and col_dir == -1)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(3);
        }
        else if (row_dir == 1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(7);
        }
        else
        {
            sprite_comp_ptr_->sprite()->set_current_frame(5);
        }
    }

    void face_component::set_idle_sprite(int row_dir, int col_dir)
    {
        if (row_dir == -1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(0);
        }
        else if (row_dir == -1 and col_dir == -1)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(2);
        }
        else if (row_dir == 1 and col_dir == 0)
        {
            sprite_comp_ptr_->sprite()->set_current_frame(6);
        }
        else
        {
            sprite_comp_ptr_->sprite()->set_current_frame(4);
        }
    }
}
