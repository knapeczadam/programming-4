#include "GameActorCommand.h"

// Project includes
#include "GameObject.h"

namespace dae
{
    void move_command::execute()
    {
        const auto go = static_cast<game_object*>(get_game_actor());
        const auto new_pos = go->get_local_position() + direction_ * speed_;
        go->set_local_position(new_pos);
    }
}
