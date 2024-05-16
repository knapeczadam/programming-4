#include "jumping_state.h"

// Project includes
#include "component/player/face_component.h"
#include "component/character/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    jumping_state::jumping_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void jumping_state::on_enter()
    {
        character_ptr_->component<face_component>()->set_sprite_orientation(3, 5, 1, 7);
        character_ptr_->component<jump_component>()->jump();
    }
}
