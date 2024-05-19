#include "npc_idle_state.h"

#include "npc_jumping_state.h"
#include "component/character/direction_component.h"
#include "component/player/face_component.h"
#include "component/state/character_state_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/utility/random.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    npc_idle_state::npc_idle_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void npc_idle_state::on_enter()
    {
        if (character_ptr_->has_tag("ball"))
        {
            character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(0);
        }
        else if (character_ptr_->has_tag("left"))
        {
            character_ptr_->component<face_component>()->set_sprite_orientation(4, 0, 4, 0, 0);
        }
        else if (character_ptr_->has_tag("right"))
        {
            character_ptr_->component<face_component>()->set_sprite_orientation(0, 0, 0, 0, 4);
        }
        else
        {
            character_ptr_->component<face_component>()->set_sprite_orientation(0, 4, 0, 0);
        }
    }

    void npc_idle_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= idle_time_)
        {
            accu_time_ = 0.0f;
            auto direction_comp_ptr = character_ptr_->component<direction_component>();
            if (character_ptr_->has_tag("down"))
            {
                int col = mngn::random_int(0, 1);
                direction_comp_ptr->set_direction(1, col);
            }
            else if (character_ptr_->has_tag("left"))
            {
                if (mngn::random_int(0, 1)) // upwards
                {
                    direction_comp_ptr->set_direction(-1, 0);
                }
                else // to the right
                {
                    direction_comp_ptr->set_direction(0, 1);
                }
            }
            else if (character_ptr_->has_tag("right"))
            {
                if (mngn::random_int(0, 1)) // upwards
                {
                    direction_comp_ptr->set_direction(-1, -1);
                }
                else // to the left
                {
                    direction_comp_ptr->set_direction(0, -1);
                }
            }
            character_ptr_->component<character_state_component>()->change_state<npc_jumping_state>(character_ptr_);
        }
    }
}
