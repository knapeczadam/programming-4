#include "descend_component.h"

// Project includes
#include "component/state/state_component.h"
#include "minigin/core/game_time.h"
#include "minigin/core/game_object.h"
#include "state/npc/npc_idle_state.h"

namespace qbert
{
    void descend_component::fixed_update()
    {
        if (is_descending_)
        {
            glm::vec2 curr_pos = owner()->local_position();
            if (curr_pos != end_pos_)
            {
                accu_time_ += mngn::game_time::instance().fixed_delta_time;
                curr_pos = glm::mix(start_pos_, end_pos_, glm::clamp(accu_time_ / descend_time_, 0.0f, 1.0f));
                owner()->set_local_position(curr_pos);
            }
            else
            {
                is_descending_ = false;
                accu_time_ = 0.0f;

                owner()->component<state_component>()->change_state<npc_idle_state>(owner());
            }
        }
    }

    void descend_component::descend(glm::vec2 const &start_pos, glm::vec2 const &end_pos)
    {
        start_pos_ = start_pos;
        end_pos_ = end_pos;
        is_descending_ = true;
    }
}
