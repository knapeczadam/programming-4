#include "npc_spawning_state.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/jump_component.h"
#include "component/npc/spawn_component.h"
#include "component/player/face_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/random.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <cstdlib>

namespace qbert
{
    npc_spawning_state::npc_spawning_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void npc_spawning_state::on_enter()
    {
        character_ptr_->component<mngn::collider_component>()->set_enabled(false);
        
        bool is_right = mngn::random_int(0, 1);
        start_pos_.x = is_right ? 256.0f : 192.0f;
        end_pos_.x = start_pos_.x;

        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(1);
        if (character_ptr_->has_tag("ball"))
        {
            character_ptr_->component<direction_component>()->set_direction(1, is_right);
        }
        else
        {
            character_ptr_->component<face_component>()->set_sprite_orientation(0, 5, 0, 1);
        }
        character_ptr_->set_local_position(start_pos_);
    }

    void npc_spawning_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= spawn_time_)
        {
            accu_time_ = 0.0f;
            character_ptr_->component<spawn_component>()->spawn(start_pos_, end_pos_);
        }
    }

    void npc_spawning_state::on_exit()
    {
        character_ptr_->component<mngn::collider_component>()->set_enabled(true);
        character_ptr_->component<jump_component>()->set_enabled(true);
    }
}
