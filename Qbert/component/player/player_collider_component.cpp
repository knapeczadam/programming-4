#include "player_collider_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/position_component.h"
#include "minigin/core/game_object.h"

// Standard includes
#include <iostream>

// GLM includes
#include <glm/glm.hpp>

#include "component/character/jump_component.h"
#include "component/state/state_component.h"
#include "state/player/colliding_state.h"

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

    void player_collider_component::on_collision_stay(mngn::game_object *other_ptr)
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
        // glm::ivec2 idle_dir = {0, 0};

        // bool this_idle = dir == idle_dir;
        // bool other_idle = other_dir == idle_dir;
        bool other_moving_to_this = pos == other_pos + other_dir;
        bool this_moving_to_other = other_pos == pos + dir;
        
        if (other_moving_to_this or this_moving_to_other)
        {
            owner()->component<state_component>()->change_state<colliding_state>(owner());
        }
        else
        {
            std::cout << "Collision detected" << std::endl;
            std::cout << "Player position: " << pos.x << ", " << pos.y << std::endl;
            std::cout << "Player direction: " << dir.x << ", " << dir.y << std::endl;
            std::cout << "Other player position: " << other_pos.x << ", " << other_pos.y << std::endl;
            std::cout << "Other player direction: " << other_dir.x << ", " << other_dir.y << std::endl;
        }
    }
}
