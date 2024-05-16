#include "dead_state.h"

#include "component/player/health_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    dead_state::dead_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }
}
