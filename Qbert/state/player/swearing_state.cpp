#include "swearing_state.h"

#include "component/player/swear_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    swearing_state::swearing_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void swearing_state::on_enter()
    {
        character_ptr_->component<swear_component>()->swear();
    }
}
