#include "idle_state.h"

// Project includes
#include "component/player/face_component.h"
#include "component/direction_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    idle_state::idle_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void idle_state::on_enter()
    {
        player_ptr_->component<face_component>()->set_idle_sprite();
        player_ptr_->component<direction_component>()->reset();
    }
}
