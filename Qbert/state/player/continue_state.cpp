#include "continue_state.h"

#include "idle_state.h"
#include "component/character/jump_component.h"
#include "component/player/player_collider_component.h"
#include "component/character/position_component.h"
#include "component/state/state_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    continue_state::continue_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void continue_state::on_enter()
    {
        character_ptr_->component<player_collider_component>()->set_enabled(true);
        character_ptr_->component<jump_component>()->set_enabled(true);
        character_ptr_->component<position_component>()->move_to_previous();
        character_ptr_->component<state_component>()->change_state<idle_state>(character_ptr_);
    }
}
