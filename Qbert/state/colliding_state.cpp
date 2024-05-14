#include "colliding_state.h"

// Project includes
#include "component/player/health_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    colliding_state::colliding_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void colliding_state::on_enter()
    {
        auto health_comp_ptr = player_ptr_->component<health_component>();
        health_comp_ptr->take_damage(1);
    }
}
