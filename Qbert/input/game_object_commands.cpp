﻿#include "game_object_commands.h"

// Project includes
#include "component/player/jump_component.h"
#include "component/player/player_state_component.h"
#include "minigin/core/game_object.h"
#include "state/idle_state.h"
#include "state/jumping_state.h"
#include "state/start_state.h"

namespace qbert
{
    void jump_command::execute()
    {
        auto player_state_comp_ptr = get_game_object()->get_component<player_state_component>();
        if (player_state_comp_ptr->is_state<start_state>() or player_state_comp_ptr->is_state<idle_state>())
        {
            player_state_comp_ptr->change_state(std::make_unique<jumping_state>(get_game_object(), row_dir_, col_dir_));
        }
    }

    void reset_move_command::execute()
    {
    }
}
