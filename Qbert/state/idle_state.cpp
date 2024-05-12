#include "idle_state.h"

// Project includes
#include "component/player/face_component.h"
#include "component/player/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    idle_state::idle_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void idle_state::on_enter()
    {
        auto jump_comp_ptr = player_ptr_->get_component<jump_component>();
        auto face_comp_ptr = player_ptr_->get_component<face_component>();
        face_comp_ptr->set_idle_sprite(jump_comp_ptr->get_row_direction(), jump_comp_ptr->get_col_direction());
    }
}
