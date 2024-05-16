﻿#include "position_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "minigin/core/game_object.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    void position_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
    }

    void position_component::update_position()
    {
        row_idx_ += direction_comp_ptr_->row();
        col_idx_ += direction_comp_ptr_->col();
        notify_observers("position_changed");
    }

    void position_component::reset(int row_idx, int col_idx)
    {
        row_idx_ = row_idx;
        col_idx_ = col_idx;
    }

    void position_component::move_to_previous()
    {
        float offset_x = 32.0f;
        float offset_y = 48.0f;

        glm::vec2 start_pos = {224.0f, 84.0f};
        glm::vec2 end_pos;
        end_pos.x = start_pos.x + (col_idx_ * 2 - row_idx_) * offset_x;
        end_pos.y = start_pos.y + (row_idx_ * offset_y);
        owner()->set_local_position(end_pos);
    }
}
