#include "start_state.h"

#include "state/player/waiting_state.h"
#include "component/state/character_state_component.h"
#include "component/character/position_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    start_state::start_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void start_state::on_enter()
    {
        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(7);
    }
}
