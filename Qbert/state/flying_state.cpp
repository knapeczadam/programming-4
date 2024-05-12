#include "flying_state.h"

// Project includes
#include "component/level/disc_component.h"
#include "component/level/fly_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    flying_state::flying_state(mngn::game_object *player_ptr, disc_component *disc_ptr)
        : player_state{player_ptr}
        , disc_ptr_{disc_ptr}
    {
    }

    void flying_state::on_enter()
    {
        player_ptr_->set_parent(disc_ptr_->get_owner());
        disc_ptr_->get_owner()->get_component<fly_component>()->fly();
    }
}
