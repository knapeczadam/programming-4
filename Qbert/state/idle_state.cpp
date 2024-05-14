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
        auto jump_comp_ptr = player_ptr_->component<jump_component>();
        auto face_comp_ptr = player_ptr_->component<face_component>();
        face_comp_ptr->set_idle_sprite(jump_comp_ptr->row_direction(), jump_comp_ptr->col_direction());
    }
}
