#include "game_object_command.h"

// Project includes
#include "core/game_object.h"

namespace dae
{
    void move_command::execute()
    {
        auto const go = static_cast<game_object*>(get_game_actor());
        auto const new_pos = go->get_local_position() + direction_ * speed_;
        go->set_local_position(new_pos);
    }
}
