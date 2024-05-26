﻿#include "swearing_state.h"

#include "state/player/dead_state.h"
#include "component/character/health_component.h"
#include "component/character/position_component.h"
#include "component/player/swear_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/audio_player.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/random.h"
#include "state/player/idle_state.h"

namespace qbert
{
    swearing_state::swearing_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void swearing_state::on_enter()
    {
        character_ptr_->component<swear_component>()->swear(true);
        scene_utility::instance().freeze_all();
        
        if (mngn::random_int(0, 1)) audio_player::instance().play(audio::qbert_swearing_1);
        else audio_player::instance().play(audio::qbert_swearing_2);
    }

    void swearing_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= swear_time_)
        {
            is_swearing_ = false;
            accu_time_  = 0.0f;
            
            // player is dead
            if (character_ptr_->component<health_component>()->health() == 0)
            {
                character_ptr_->component<character_state_component>()->change_state<dead_state>(character_ptr_);
            }
            else
            {
                character_ptr_->component<character_state_component>()->change_state<idle_state>(character_ptr_);
            }
        }
    }

    void swearing_state::on_exit()
    {
        scene_utility::instance().unfreeze_all();
        scene_utility::instance().trigger_npcs();
        
        character_ptr_->component<swear_component>()->swear(false);
        character_ptr_->component<position_component>()->move_to_previous();
    }
}
