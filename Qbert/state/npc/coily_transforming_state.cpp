#include "coily_transforming_state.h"

// Project includes
#include "coily_idle_state.h"
#include "npc_jumping_state.h"
#include "component/npc/coily_component.h"
#include "component/state/character_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    coily_transforming_state::coily_transforming_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void coily_transforming_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= transform_time_)
        {
            character_ptr_->component<coily_component>()->transform();
            character_ptr_->component<coily_component>()->calculate_next_move();
            character_ptr_->component<character_state_component>()->change_state<npc_jumping_state>(character_ptr_);
            accu_time_ = 0.0f;
        }
    }
}
