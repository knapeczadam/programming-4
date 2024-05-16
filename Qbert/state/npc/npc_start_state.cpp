#include "npc_start_state.h"

// Project includes
#include "minigin/core/game_object.h"
#include "component/npc/descend_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/utility/sprite.h"
#include "minigin/utility/random.h"

// Standard includes
#include <cstdlib>

// GLM includes
#include <glm/glm.hpp>

#include "component/character/position_component.h"

namespace qbert
{
    npc_start_state::npc_start_state(mngn::game_object *character_ptr)
        : character_state(character_ptr)
    {
    }

    void npc_start_state::on_enter()
    {
        glm::vec2 start_pos;
        glm::vec2 end_pos = {0.0f, 132.0f};

        bool is_left = mngn::random_int(0, 1);
        if (is_left)
        {
            start_pos = {192.0f, -32.0f};
            character_ptr_->component<position_component>()->set_col(0);
        }
        else
        {
            start_pos = {256.0f, -32.0f};
            character_ptr_->component<position_component>()->set_col(1);
        }
        end_pos.x = start_pos.x;

        character_ptr_->component<descend_component>()->descend(start_pos, end_pos);
        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(1);
    }
}
