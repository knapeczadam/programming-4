#include "game_object_commands.h"

// Project includes
#include "component/direction_component.h"
#include "component/player/jump_component.h"
#include "component/player/player_state_component.h"
#include "minigin/core/game_object.h"
#include "state/player/idle_state.h"
#include "state/player/jumping_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    void jump_command::execute()
    {
        auto player_state_comp_ptr = game_object()->component<player_state_component>();
        if (player_state_comp_ptr->is_state<start_state>() or player_state_comp_ptr->is_state<idle_state>())
        {
            auto direction_comp_ptr = game_object()->component<direction_component>();
            direction_comp_ptr->set_direction(row_dir_, col_dir_);
            player_state_comp_ptr->change_state<jumping_state>(game_object());
        }
    }
}
