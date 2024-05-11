﻿#include "jump_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    void jump_component::fixed_update()
    {
        if (is_jumping_)
        {
            if (curr_pos_ != end_pos_)
            {
                accu_time_ += mngn::game_time::get_instance().fixed_delta_time;
                calculate_bezier_curve();
                get_owner()->set_local_position(curr_pos_);
            }
            else
            {
                is_jumping_ = false;
                accu_time_ = 0.0f;
                notify_observers("jump_finished");
            }
        }
    }

    void jump_component::jump(int row, int col)
    {
        row_ = row;
        col_ = col;
        is_jumping_ = true;
        calculate_end_position(row, col);
        notify_observers("jump_started");
    }

    void jump_component::calculate_end_position(int row, int col)
    {
        start_pos_ = get_owner()->get_local_position();
        
        int offset_x = 32;
        int offset_y = 48;

        if (row_ == 1 and col_ == 0) col = -1;
        if (row_ == -1 and col_ == 0) col = 1;

        end_pos_.x = start_pos_.x + col * offset_x;
        end_pos_.y = start_pos_.y + row * offset_y;
    }

    void jump_component::calculate_bezier_curve()
    {
        float t = accu_time_ / jump_time_;
        t = glm::clamp(t, 0.0f, 1.0f);

        glm::vec2 p0 = start_pos_;
        glm::vec2 p1;
        glm::vec2 p2;
        glm::vec2 p3 = end_pos_;
        glm::vec2 corner;

        // I-II. quadrants (top right, top left)
        if (row_ == -1)
        {
            corner = {start_pos_.x, end_pos_.y};
        }
        // III-IV. quadrants (bottom left, bottom right)
        else if (row_ == 1)
        {
            corner = {end_pos_.x, start_pos_.y};
        }
        
        p1 = (start_pos_ + corner) / 2.0f;
        p2 = (end_pos_   + corner) / 2.0f;

        auto p01  = glm::mix(p0,  p1,  t);
        auto p12  = glm::mix(p1,  p2,  t);
        auto p23  = glm::mix(p2,  p3,  t);
        auto p012 = glm::mix(p01, p12, t);
        auto p123 = glm::mix(p12, p23, t);
        
        curr_pos_ = glm::mix(p012, p123, t);
    }
}
