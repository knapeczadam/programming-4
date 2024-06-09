#include "player_collider_component.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/health_component.h"
#include "component/character/position_component.h"
#include "component/player/score_counter_component.h"
#include "component/state/character_state_component.h"
#include "core/audio_player.h"
#include "minigin/core/game_object.h"
#include "state/player/idle_state.h"
#include "state/player/jumping_state.h"
#include "state/player/start_state.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    player_collider_component::player_collider_component(float width, float height, float offset_x, float offset_y)
        : mngn::collider_component{width, height, offset_x, offset_y}
    {
    }

    void player_collider_component::awake()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
        position_comp_ptr_  = owner()->component<position_component>();
    }

    void player_collider_component::on_enable()
    {
        direction_comp_ptr_ = owner()->component<direction_component>();
        position_comp_ptr_  = owner()->component<position_component>();
    }

    void player_collider_component::on_collision_stay(mngn::game_object *other_ptr)
    {
        auto state_comp_ptr = owner()->component<character_state_component>();
        if (state_comp_ptr->is_state<start_state>() or state_comp_ptr->is_state<idle_state>() or state_comp_ptr->is_state<jumping_state>())
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
            if (other_ptr->has_tag("position_offset")) other_pos += 1;
            glm::ivec2 dir = {row_dir, col_dir};
            glm::ivec2 other_dir = {other_row_dir, other_col_dir};
            glm::ivec2 idle_dir = {0, 0};

            bool idle = dir == idle_dir;
            bool other_idle = other_dir == idle_dir;
            bool moving_to_other = pos + dir == other_pos;
            bool other_moving_to_this = other_pos + other_dir == pos;
        
            bool crossing_each_other = moving_to_other and other_moving_to_this;
            bool moving_to_the_same_pos = pos + dir == other_pos + other_dir;
            bool idle_and_other_moving_to_this = idle and other_moving_to_this;
            bool other_idle_and_this_moving_to_other = other_idle and moving_to_other;
            bool both_idle_and_same_pos = idle and other_idle and pos == other_pos;

            if (crossing_each_other or idle_and_other_moving_to_this or other_idle_and_this_moving_to_other or both_idle_and_same_pos or moving_to_the_same_pos)
            {
                if (other_ptr->has_tag("friend"))
                {
                    other_ptr->component<health_component>()->take_damage(1);
                    if (other_ptr->has_tag("ball"))
                    {
                        owner()->component<score_counter_component>()->add_score(100);
                        notify_observers("extra_time");
                    }
                    else // slick or sam
                    {
                        owner()->component<score_counter_component>()->add_score(300);
                    }
                }
                else
                {
                    if (other_ptr->has_tag("ball"))
                    {
                        audio_player::instance().play(audio::ball_bump);
                    }
                    else if (other_ptr->has_tag("coily"))
                    {
                        audio_player::instance().play(audio::coily_bump);
                    }
                    owner()->component<health_component>()->take_damage(1);
                }
            }
        }
    }
}
