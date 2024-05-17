#include "state_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "state/null_state.h"
#include "state/npc/npc_spawning_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    state_component::state_component()
    {
        state_ = std::make_unique<null_state>();
    }

    void state_component::start()
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

    void state_component::update()
    {
        state_->update();
    }
}
