#include "npc_start_state.h"

// Project includes
#include "minigin/core/game_object.h"
#include "component/npc/descend_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <cstdlib>

// GLM includes
#include <glm/glm.hpp>

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
        
        if (std::rand() % 2)
        {
            start_pos = {192.0f, -32.0f};
        }
        else
        {
            start_pos = {256.0f, -32.0f};
        }
        end_pos.x = start_pos.x;

        character_ptr_->component<descend_component>()->descend(start_pos, end_pos);
        character_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(1);
    }
}
