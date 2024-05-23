#include "game_object_commands.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/coop_state.h"
#include "state/game/single_state.h"
#include "state/game/versus_state.h"
#include "state/player/idle_state.h"
#include "state/player/jumping_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    void jump_command::execute()
    {
        auto scene_ptr = mngn::scene_manager::instance().find("game_state");
        auto game_state_go_ptr = scene_ptr->find("game_state");
        auto game_state_comp_ptr = game_state_go_ptr->component<game_state_component>();
        
        if (game_state_comp_ptr->is_state<single_state>() or game_state_comp_ptr->is_state<coop_state>() or game_state_comp_ptr->is_state<versus_state>())
        {
            auto player_state_comp_ptr = game_object_ptr_->component<character_state_component>();
            if (player_state_comp_ptr->owner()->scene()->active() and (player_state_comp_ptr->is_state<start_state>() or
                player_state_comp_ptr->is_state<idle_state>()))
            {
                auto direction_comp_ptr = game_object_ptr_->component<direction_component>();
                direction_comp_ptr->set_direction(row_dir_, col_dir_);
                player_state_comp_ptr->change_state<jumping_state>(game_object_ptr_);
            }
        }
    }
}
