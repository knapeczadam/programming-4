#include "start_state.h"

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
        auto sprite_comp_ptr_ = player_ptr_->get_component<mngn::sprite_component>();
        sprite_comp_ptr_->get_sprite()->set_current_frame(7);

        player_ptr_->set_local_position(224.0f, 84.0f);
    }
}
