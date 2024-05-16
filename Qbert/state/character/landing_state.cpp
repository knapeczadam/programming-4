#include "landing_state.h"

// Project includes
#include "component/character/position_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    landing_state::landing_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void landing_state::on_enter()
    {
        character_ptr_->component<position_component>()->update_position();
    }
}
