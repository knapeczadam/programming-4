#include "jumping_state.h"

// Project includes
#include "component/player/face_component.h"
#include "component/player/jump_component.h"
#include "component/player/position_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    jumping_state::jumping_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void jumping_state::on_enter()
    {
        player_ptr_->component<face_component>()->set_jump_sprite();
        player_ptr_->component<jump_component>()->jump();
    }
}
