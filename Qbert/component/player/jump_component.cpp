#include "jump_component.h"

// Project includes
#include "player_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "state/landing_state.h"
#include "minigin/utility/math.h"

// Standard includes
#include <iostream>


namespace qbert
{
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

    void jump_component::jump(int row_dir, int col_dir)
    {
        row_dir_ = row_dir;
        col_dir_ = col_dir;
        is_jumping_ = true;
        calculate_bezier_positions(row_dir, col_dir);
    }

    void jump_component::calculate_bezier_positions(int row_dir, int col_dir)
    {
        start_pos_ = owner()->local_position();
        
        int offset_x = 32;
        int offset_y = 48;

        if (row_dir_ == 1 and col_dir_ == 0) col_dir = -1;
        if (row_dir_ == -1 and col_dir_ == 0) col_dir = 1;

        end_pos_.x = start_pos_.x + col_dir * offset_x;
        end_pos_.y = start_pos_.y + row_dir * offset_y;
        
        // I-II. quadrants (top right, top left)
        if (row_dir_ == -1)
        {
            corner_pos_ = {start_pos_.x, end_pos_.y};
        }
        // III-IV. quadrants (bottom left, bottom right)
        else if (row_dir_ == 1)
        {
            corner_pos_ = {end_pos_.x, start_pos_.y};
        }
        
        pos_1_ = (start_pos_ + corner_pos_) / 2.0f;
        pos_2_ = (end_pos_   + corner_pos_) / 2.0f;
    }
}
