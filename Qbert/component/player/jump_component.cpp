#include "jump_component.h"

// Project includes
#include "player_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "state/landing_state.h"

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
                accu_time_ += mngn::game_time::get_instance().fixed_delta_time;
                calculate_bezier_curve();
                get_owner()->set_local_position(curr_pos_);
            }
            else
            {
                is_jumping_ = false;
                accu_time_ = 0.0f;
                
                auto player_state_comp_ptr = get_owner()->get_component<player_state_component>();
                player_state_comp_ptr->change_state(std::make_unique<landing_state>(get_owner()));
            }
        }
    }

    void jump_component::jump(int row_dir, int col_dir)
    {
        row_dir_ = row_dir;
        col_dir_ = col_dir;
        is_jumping_ = true;
        calculate_end_position(row_dir, col_dir);
    }

    void jump_component::calculate_end_position(int row_dir, int col_dir)
    {
        start_pos_ = get_owner()->get_local_position();
        
        int offset_x = 32;
        int offset_y = 48;

        if (row_dir_ == 1 and col_dir_ == 0) col_dir = -1;
        if (row_dir_ == -1 and col_dir_ == 0) col_dir = 1;

        end_pos_.x = start_pos_.x + col_dir * offset_x;
        end_pos_.y = start_pos_.y + row_dir * offset_y;

        std::cout << "Start pos: " << start_pos_.x << ", " << start_pos_.y << std::endl;
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
        if (row_dir_ == -1)
        {
            corner = {start_pos_.x, end_pos_.y};
        }
        // III-IV. quadrants (bottom left, bottom right)
        else if (row_dir_ == 1)
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
