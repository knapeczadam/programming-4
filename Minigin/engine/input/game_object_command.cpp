#include "game_object_command.h"

// Project includes
#include "move_component.h"
#include "core/game_object.h"

namespace dae
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
