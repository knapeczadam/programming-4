﻿#include "npc_dead_state.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/health_component.h"
#include "component/character/jump_component.h"
#include "component/character/position_component.h"
#include "component/npc/coily_component.h"
#include "component/player/score_counter_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "state/game/game_over_state.h"
#include "state/npc/npc_spawning_state.h"

namespace qbert
{
    npc_dead_state::npc_dead_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void npc_dead_state::on_enter()
    {
        character_ptr_->component<health_component>()->heal(1);
        character_ptr_->component<jump_component>()->set_enabled(false);
        character_ptr_->component<direction_component>()->reset();
        
        if (character_ptr_->has_tag("down"))
        {
            character_ptr_->component<position_component>()->reset();
        }
        else if (character_ptr_->has_tag("left"))
        {
            character_ptr_->component<position_component>()->reset(6, 0);
        }
        else if (character_ptr_->has_tag("right"))
        {
            character_ptr_->component<position_component>()->reset(6, 6);
        }

        if (character_ptr_->has_tag("coily"))
        {
            character_ptr_->component<coily_component>()->transform_back();
            if (not scene_utility::instance().game_state()->is_state<game_over_state>())
            {
                scene_utility::instance().current_scene()->find_game_objects_with_tag("player").front()->component<score_counter_component>()->add_score(500);
            }
        }
        
        character_ptr_->component<character_state_component>()->change_state<npc_spawning_state>(character_ptr_);
    }
}
