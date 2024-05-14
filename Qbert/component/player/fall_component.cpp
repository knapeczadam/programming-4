#include "fall_component.h"

// Project includes
#include "player_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/math.h"
#include "state/start_state.h"

// Standard includes
#include <iostream>

#include "state/waiting_state.h"

namespace qbert
{
    void fall_component::fixed_update()
    {
        if (is_falling_)
        {
            if (curr_pos_ != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time;
                float t = accu_time_ / fall_time_;
                t = glm::clamp(t, 0.0f, 1.0f);
                
                curr_pos_ = mngn::bezier_curve(start_pos_, pos_1_, pos_2_, end_pos_, t);
                owner()->set_local_position(curr_pos_);
            }
            else
            {
                is_falling_ = false;
                accu_time_ = 0.0f;
                curr_pos_ = {};
                
                auto player_state_comp_ptr = owner()->component<player_state_component>();
                player_state_comp_ptr->change_state<waiting_state>(owner(), 1.0f);
            }
        }
    }

    void fall_component::fall(int col_idx)
    {
        is_falling_ = true;
        calculate_bezier_positions(col_idx);
    }

    void fall_component::calculate_bezier_positions(int col_idx)
    {
        float offset_x = 96.0f;
        start_pos_ = owner()->local_position();
        
        if (col_idx == -1)
        {
            corner_pos_ = {start_pos_.x - offset_x, start_pos_.y};
            end_pos_.x = start_pos_.x - offset_x;
        }
        else
        {
            corner_pos_ = {start_pos_.x + offset_x, start_pos_.y};
            end_pos_.x = start_pos_.x + offset_x;
        }

        pos_1_ = (start_pos_ + corner_pos_) / 2.0f;
        pos_2_ = (end_pos_ + corner_pos_) / 2.0f;
    }
}
