#include "colliding_state.h"

// Project includes
#include "swearing_state.h"
#include "component/character/jump_component.h"
#include "component/player/health_component.h"
#include "component/player/player_collider_component.h"
#include "component/state/state_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    colliding_state::colliding_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void colliding_state::on_enter()
    {
        character_ptr_->component<player_collider_component>()->set_enabled(false);
        character_ptr_->component<jump_component>()->set_enabled(false);
        character_ptr_->component<state_component>()->change_state<swearing_state>(character_ptr_);
    }
}
