#include "position_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "minigin/core/game_object.h"
#include "state/player/waiting_state.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    position_component::position_component(int row_idx, int col_idx)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
        , original_row_idx_{row_idx}
        , original_col_idx_{col_idx}
    {
    }

    void position_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
        original_position_ = owner()->local_position();
    }

    void position_component::on_enable()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
        original_position_ = owner()->local_position();
    }

    void position_component::on_disable()
    {
        row_idx_ = original_row_idx_;
        col_idx_ = original_col_idx_;
        owner()->set_local_position(original_position_);
    }

    void position_component::update_position()
    {
        if (owner()->component<character_state_component>()->is_state<waiting_state>())
        {
            notify_observers("update_cube");
            return;
        }
        row_idx_ += direction_comp_ptr_->row();
        col_idx_ += direction_comp_ptr_->col();
        notify_observers("position_changed");

        if (owner()->has_tag("player") or owner()->has_tag("friend"))
        {
            notify_observers("update_cube");
        }
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
