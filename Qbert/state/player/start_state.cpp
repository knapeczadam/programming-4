#include "start_state.h"

#include "component/player/position_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    start_state::start_state(mngn::game_object *player_ptr)
        : player_state{player_ptr}
    {
    }

    void start_state::on_enter()
    {
        player_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(7);
    }
}
