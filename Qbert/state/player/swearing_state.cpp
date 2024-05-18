#include "swearing_state.h"

#include "component/player/swear_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "component/character/jump_component.h"
#include "component/player/player_collider_component.h"
#include "component/character/position_component.h"
#include "component/state/character_state_component.h"
#include "idle_state.h"

namespace qbert
{
    swearing_state::swearing_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void swearing_state::on_enter()
    {
        character_ptr_->component<swear_component>()->swear(true);
        character_ptr_->component<player_collider_component>()->set_enabled(false);
        character_ptr_->component<jump_component>()->set_enabled(false);
    }

    void swearing_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= swear_time_)
        {
            is_swearing_ = false;
            accu_time_  = 0.0f;
            character_ptr_->component<character_state_component>()->change_state<idle_state>(character_ptr_);
        }
    }

    void swearing_state::on_exit()
    {
        character_ptr_->component<swear_component>()->swear(false);
        character_ptr_->component<player_collider_component>()->set_enabled(true);
        character_ptr_->component<jump_component>()->set_enabled(true);
        character_ptr_->component<position_component>()->move_to_previous();
    }
}
