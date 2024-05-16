#include "npc_jumping_state.h"

#include "component/character/jump_component.h"
#include "component/player/face_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    npc_jumping_state::npc_jumping_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void npc_jumping_state::on_enter()
    {
        if (character_ptr_->has_tag("ball"))
        {
            character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(1);
        }
        else
        {
            character_ptr_->component<face_component>()->set_sprite_orientation(0, 5, 0, 1);
        }
        character_ptr_->component<jump_component>()->jump();
    }
}
