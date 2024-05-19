#include "character_state_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "state/npc/npc_spawning_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    void character_state_component::start()
    {
        init_state();
    }

    void character_state_component::on_disable()
    {
        init_state();
    }

    void character_state_component::init_state()
    {
        if (owner()->has_tag("player"))
        {
            change_state<start_state>(owner());
        }
        else if (owner()->has_tag("npc"))
        {
            change_state<npc_spawning_state>(owner());
        }
    }
}
