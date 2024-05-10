﻿#include "game_object_commands.h"

// Project includes
#include "component/move_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void move_command::execute()
    {
        get_game_object()->get_component<move_component>()->set_direction(direction_);
    }

    void reset_move_command::execute()
    {
        get_game_object()->get_component<move_component>()->stop_moving();
    }
}