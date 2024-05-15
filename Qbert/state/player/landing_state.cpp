#include "landing_state.h"

// Project includes
#include "component/player/jump_component.h"
#include "component/player/position_idx_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    landing_state::landing_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void landing_state::on_enter()
    {
        auto jump_comp_ptr = player_ptr_->component<jump_component>();
        auto position_comp_ptr = player_ptr_->component<position_idx_component>();
        position_comp_ptr->set_position_idx(jump_comp_ptr->row_direction(), jump_comp_ptr->col_direction());
    }
}
