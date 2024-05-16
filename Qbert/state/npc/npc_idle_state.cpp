#include "npc_idle_state.h"

#include "npc_jumping_state.h"
#include "component/character/direction_component.h"
#include "component/state/state_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    npc_idle_state::npc_idle_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void npc_idle_state::on_enter()
    {
        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(0);
    }

    void npc_idle_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= idle_time_)
        {
            accu_time_ = 0.0f;
            auto direction_comp_ptr = character_ptr_->component<direction_component>();
            int col = std::rand() % 2;
            direction_comp_ptr->set_direction(1, col);
            character_ptr_->component<state_component>()->change_state<npc_jumping_state>(character_ptr_);
        }

    }
}
