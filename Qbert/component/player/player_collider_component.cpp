#include "player_collider_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/position_component.h"
#include "minigin/core/game_object.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    player_collider_component::player_collider_component(float width, float height)
        : mngn::collider_component{width, height}
    {
    }

    void player_collider_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
        position_comp_ptr_  = owner()->component<position_component>();
    }

    void player_collider_component::on_trigger_enter(mngn::game_object *other_ptr)
    {
        auto row_pos       = position_comp_ptr_->row();
        auto col_pos       = position_comp_ptr_->col();
        auto other_row_pos = other_ptr->component<position_component>()->row();
        auto other_col_pos = other_ptr->component<position_component>()->col();
        auto row_dir       = owner()->component<direction_component>()->row();
        auto col_dir       = owner()->component<direction_component>()->col();
        auto other_row_dir = other_ptr->component<direction_component>()->row();
        auto other_col_dir = other_ptr->component<direction_component>()->col();

        glm::ivec2 pos = {row_pos, col_pos};
        glm::ivec2 other_pos = {other_row_pos, other_col_pos};
        glm::ivec2 dir = {row_dir, col_dir};
        glm::ivec2 other_dir = {other_row_dir, other_col_dir};
        glm::ivec2 idle = {0, 0};

        if (dir == idle and pos == other_pos + other_dir)
        {
            // player is idle and other player is moving towards it
        }
        else if (other_dir == idle and other_pos == pos + dir)
        {
            // other player is idle and player is moving towards it
        }
        else if (pos == other_pos + other_dir and other_pos == pos + dir)
        {
            // both players are moving towards each other
        }
    }
}
