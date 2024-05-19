#include "waiting_state.h"

// Project includes
#include "start_state.h"
#include "component/state/character_state_component.h"
#include "component/character/position_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    waiting_state::waiting_state(mngn::game_object* character_ptr, float waiting_time)
        : character_state{character_ptr}
        , waiting_time_{waiting_time}
    {
    }

    void waiting_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= waiting_time_)
        {
            character_ptr_->component<character_state_component>()->change_state<start_state>(character_ptr_);
            accu_time_ = 0.0f;
        }
    }

    void waiting_state::on_exit()
    {
        character_ptr_->set_local_position(224.0f, 84.0f);
        character_ptr_->component<position_component>()->reset();
    }
}
