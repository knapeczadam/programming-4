#include "start_state.h"

// Project includes
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    start_state::start_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void start_state::on_enter()
    {
        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(7);
        
        if (character_ptr_->has_tag("menu_2"))
            character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(5);
    }
}
