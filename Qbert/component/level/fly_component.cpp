﻿#include "fly_component.h"

// Project includes
#include "component/state/character_state_component.h"
#include "core/audio_player.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "state/player/flying_state.h"

namespace qbert
{
    void fly_component::start()
    {
        start_pos_ = owner()->local_position();
    }

    void fly_component::fixed_update()
    {
        if (frozen_) return;
        
        if (is_flying_)
        {
            glm::vec2 curr_pos = owner()->local_position();
            if (curr_pos != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time();
                curr_pos = glm::mix(start_pos_, end_pos_, glm::clamp(accu_time_ / fly_time_, 0.0f, 1.0f));
                owner()->set_local_position(curr_pos);
            }
            else
            {
                is_flying_ = false;
                accu_time_ = 0.0f;

                auto const root_ptr = owner()->parent();
                auto const player_states = root_ptr->components_in_children<character_state_component>();
                for (auto const &player_state : player_states)
                {
                    if (player_state->is_state<flying_state>())
                    {
                        auto const player_ptr = player_state->owner();
                        player_ptr->set_parent(root_ptr);
                    }
                }
            }
        }
    }

    void fly_component::on_disable()
    {
        is_flying_ = false;
        accu_time_ = 0.0f;
    }

    void fly_component::fly()
    {
        is_flying_ = true;
        audio_player::instance().play(audio::disk_lift);
    }
}
