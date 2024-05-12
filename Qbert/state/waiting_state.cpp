#include "waiting_state.h"

// Project includes
#include "start_state.h"
#include "component/player/player_state_component.h"
#include "component/player/position_idx_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    waiting_state::waiting_state(mngn::game_object* player_ptr)
        : player_state{player_ptr}
    {
    }

    void waiting_state::update()
    {
        accu_time += mngn::game_time::get_instance().delta_time;
        if (accu_time >= waiting_time)
        {
            player_ptr_->get_component<player_state_component>()->change_state<start_state>(player_ptr_);
            accu_time = 0.0f;
        }
    }

    void waiting_state::on_exit()
    {
        player_ptr_->set_local_position(224.0f, 84.0f);
        
        auto position_comp_ptr = player_ptr_->get_component<position_idx_component>();
        position_comp_ptr->reset_position_idx();
    }
}
