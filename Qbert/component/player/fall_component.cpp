#include "fall_component.h"

// Project includes
#include "component/player/health_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/math.h"

namespace qbert
{
    void fall_component::fixed_update()
    {
        if (is_falling_)
        {
            if (curr_pos_ != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time();
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

                owner()->component<health_component>()->take_damage(1);
            }
        }
    }

    void fall_component::fall(int row_dir, int col_dir, int row_idx, int col_idx)
    {
        is_falling_ = true;
        calculate_bezier_positions(row_dir, col_dir, row_idx, col_idx);
    }

    void fall_component::calculate_bezier_positions([[maybe_unused]] int row_dir, [[maybe_unused]] int col_dir, [[maybe_unused]] int row_idx, int col_idx)
    {
        float offset_x = 96.0f;
        float offset_y = 96.0f;
        start_pos_ = owner()->local_position();

        if (col_idx == -1)
        {
            if (owner()->has_tag("right"))
            {
                end_pos_ = {-32.0f, start_pos_.y - offset_y};
                corner_pos_ = (start_pos_ + end_pos_) / 2.0f;
            }
            else
            {
                corner_pos_ = {start_pos_.x - offset_x, start_pos_.y};
                end_pos_.x = start_pos_.x - offset_x;
            }
        }
        else if (row_idx == 7)
        {
            if (row_dir == col_dir)
            {
                end_pos_.x = start_pos_.x + offset_x / 3.0f;
                corner_pos_ = (start_pos_ + end_pos_) / 2.0f;
            }
            else
            {
                end_pos_.x = start_pos_.x - offset_x / 3.0f;
                corner_pos_ = (start_pos_ + end_pos_) / 2.0f;
            }
        }
        else if (col_idx > row_idx)
        {
            if (owner()->has_tag("left"))
            {
                end_pos_ = {480.0f, start_pos_.y - offset_y};
                corner_pos_ = (start_pos_ + end_pos_) / 2.0f;
            }
            else
            {
                corner_pos_ = {start_pos_.x + offset_x, start_pos_.y};
                end_pos_.x = start_pos_.x + offset_x;
            }
        }

        pos_1_ = (start_pos_ + corner_pos_) / 2.0f;
        pos_2_ = (end_pos_ + corner_pos_) / 2.0f;
    }
}
