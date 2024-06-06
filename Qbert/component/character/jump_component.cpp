#include "jump_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/math.h"
#include "position_component.h"
#include "core/audio_player.h"

namespace qbert
{
    void jump_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void jump_component::on_enable()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void jump_component::fixed_update()
    {
        if (frozen_) return;
        
        if (is_jumping_)
        {
            if (curr_pos_ != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time();
                float t = glm::clamp(accu_time_ / jump_time_, 0.0f, 1.0f);
                curr_pos_ = mngn::bezier_curve(start_pos_, pos_1_, pos_2_, end_pos_, t);
                owner()->set_local_position(curr_pos_);
            }
            else
            {
                is_jumping_ = false;
                accu_time_ = 0.0f;
                owner()->component<position_component>()->update_position();

                if (owner()->has_tag("loading")) audio_player::instance().play(audio::qbert_jump);
            }
        }
    }

    void jump_component::on_disable()
    {
        reset();
    }

    void jump_component::jump()
    {
        is_jumping_ = true;
        calculate_bezier_positions();
    }

    void jump_component::reset()
    {
        is_jumping_ = false;
        accu_time_ = 0.0f;
        curr_pos_ = {};
    }

    void jump_component::calculate_bezier_positions()
    {
        start_pos_ = owner()->local_position();
        int row_dir = direction_comp_ptr_->row();
        int col_dir = direction_comp_ptr_->col();
        
        int offset_x = 32;
        int offset_y = 48;
        int offset_x_diagonal = 64;

        if (row_dir == 1 and col_dir == 0) col_dir = -1;
        else if (row_dir == -1 and col_dir == 0) col_dir = 1;

        end_pos_.x = start_pos_.x + col_dir * offset_x;
        end_pos_.y = start_pos_.y + row_dir * offset_y;
        
        if (row_dir == 0)
        {
            end_pos_.x = start_pos_.x + col_dir * offset_x_diagonal;
            end_pos_.y = start_pos_.y;
        }

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
        else if (row_dir == 0)
        {
            corner_pos_.x = (start_pos_.x + end_pos_.x) / 2.0f;
            corner_pos_.y = end_pos_.y + offset_y;
        }
        
        pos_1_ = (start_pos_ + corner_pos_) / 2.0f;
        pos_2_ = (end_pos_   + corner_pos_) / 2.0f;
    }
}
