#include "jump_component.h"

// Project includes
#include "component/player/player_state_component.h"
#include "component/direction_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "state/player/landing_state.h"
#include "minigin/utility/math.h"

namespace qbert
{
    void jump_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void jump_component::fixed_update()
    {
        if (is_jumping_)
        {
            if (curr_pos_ != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time;
                float t = accu_time_ / jump_time_;
                t = glm::clamp(t, 0.0f, 1.0f);
                curr_pos_ = mngn::bezier_curve(start_pos_, pos_1_, pos_2_, end_pos_, t);
                owner()->set_local_position(curr_pos_);
            }
            else
            {
                is_jumping_ = false;
                accu_time_ = 0.0f;
                curr_pos_ = {};
                
                auto player_state_comp_ptr = owner()->component<player_state_component>();
                player_state_comp_ptr->change_state<landing_state>(owner());
            }
        }
    }

    void jump_component::jump()
    {
        is_jumping_ = true;
        calculate_bezier_positions();
    }

    void jump_component::calculate_bezier_positions()
    {
        start_pos_ = owner()->local_position();
        int row_dir = direction_comp_ptr_->row();
        int col_dir = direction_comp_ptr_->col();
        
        int offset_x = 32;
        int offset_y = 48;

        if (row_dir == 1 and col_dir == 0) col_dir = -1;
        else if (row_dir == -1 and col_dir == 0) col_dir = 1;

        end_pos_.x = start_pos_.x + col_dir * offset_x;
        end_pos_.y = start_pos_.y + row_dir * offset_y;
        
        // I-II. quadrants (top right, top left)
        if (row_dir == -1)
        {
            corner_pos_ = {start_pos_.x, end_pos_.y};
        }
        // III-IV. quadrants (bottom left, bottom right)
        else if (row_dir == 1)
        {
            corner_pos_ = {end_pos_.x, start_pos_.y};
        }
        
        pos_1_ = (start_pos_ + corner_pos_) / 2.0f;
        pos_2_ = (end_pos_   + corner_pos_) / 2.0f;
    }
}
