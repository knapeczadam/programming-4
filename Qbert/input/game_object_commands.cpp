﻿#include "game_object_commands.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/coop_state.h"
#include "state/game/single_state.h"
#include "state/game/versus_state.h"
#include "state/npc/npc_idle_state.h"
#include "state/player/idle_state.h"
#include "state/player/jumping_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    void jump_command::execute()
    {
        auto const game_state_comp_ptr = scene_utility::instance().game_state();

        if (game_object_ptr_->has_tag("player"))
        {
            if (game_state_comp_ptr->is_state<single_state>() or game_state_comp_ptr->is_state<coop_state>() or game_state_comp_ptr->is_state<versus_state>())
            {
                auto const character_state_comp_ = game_object_ptr_->component<character_state_component>();
                auto const scene_ptr = scene_utility::instance().current_scene();\
                if (scene_ptr->name() == game_object_ptr_->scene()->name())
                {
                    if (character_state_comp_->owner()->scene()->active() and (character_state_comp_->is_state<start_state>() or character_state_comp_->is_state<idle_state>()))
                    {
                        auto const direction_comp_ptr = game_object_ptr_->component<direction_component>();
                        direction_comp_ptr->set_direction(row_dir_, col_dir_);
                        character_state_comp_->change_state<jumping_state>(game_object_ptr_);
                    }
                }
            }
        }
        else if (game_object_ptr_->has_tag("coily"))
        {
            if (game_state_comp_ptr->is_state<versus_state>())
            {
                auto const character_state_comp_ = game_object_ptr_->component<character_state_component>();
                auto const scene_ptr = scene_utility::instance().current_scene();
                if (scene_ptr->name() == game_object_ptr_->scene()->name())
                {
                    if (character_state_comp_->owner()->scene()->active() and character_state_comp_->is_state<npc_idle_state>())
                    {
                        auto const direction_comp_ptr = game_object_ptr_->component<direction_component>();
                        direction_comp_ptr->set_direction(row_dir_, col_dir_);
                        character_state_comp_->change_state<jumping_state>(game_object_ptr_);
                    }
                }
            }
        }
    }
}
