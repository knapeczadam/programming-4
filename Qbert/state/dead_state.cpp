#include "dead_state.h"

#include "component/player/health_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    dead_state::dead_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void dead_state::on_enter()
    {
        auto health_comp_ptr = player_ptr_->get_component<health_component>();
        health_comp_ptr->take_damage(1);
    }
}
