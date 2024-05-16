#include "npc_dead_state.h"

#include "npc_start_state.h"
#include "component/character/position_component.h"
#include "component/player/health_component.h"
#include "component/state/state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    npc_dead_state::npc_dead_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void npc_dead_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= dead_time_)
        {
            accu_time_ = 0.0f;
            character_ptr_->component<state_component>()->change_state<npc_start_state>(character_ptr_);
        }
    }

    void npc_dead_state::on_exit()
    {
        character_ptr_->component<health_component>()->heal(1);
        character_ptr_->component<position_component>()->reset(1);
    }
}
