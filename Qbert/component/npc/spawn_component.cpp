﻿#include "spawn_component.h"

// Project includes
#include "component/character/position_component.h"
#include "component/state/character_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    void spawn_component::fixed_update()
    {
        if (is_spawning_)
        {
            glm::vec2 curr_pos = owner()->local_position();
            if (curr_pos != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time;
                curr_pos = glm::mix(start_pos_, end_pos_, glm::clamp(accu_time_ / spawn_time_, 0.0f, 1.0f));
                owner()->set_local_position(curr_pos);
            }
            else
            {
                is_spawning_ = false;
                accu_time_ = 0.0f;

                owner()->component<position_component>()->update_position();
            }
        }
    }

    void spawn_component::spawn(glm::vec2 const &start_pos, glm::vec2 const &end_pos)
    {
        start_pos_   = start_pos;
        end_pos_     = end_pos;
        is_spawning_ = true;
    }
}
