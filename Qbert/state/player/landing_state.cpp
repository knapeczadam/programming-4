#include "landing_state.h"

// Project includes
#include "component/player/position_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    landing_state::landing_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void landing_state::on_enter()
    {
        player_ptr_->component<position_component>()->update_position();
    }
}
