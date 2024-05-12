#include "fly_component.h"

// Project includes
#include "component/player/player_state_component.h"
#include "minigin/core/game_time.h"
#include "minigin/core/game_object.h"
#include "state/flying_state.h"
#include "state/start_state.h"

namespace qbert
{
    fly_component::fly_component(glm::vec2 start_pos)
        : start_pos_(start_pos)
    {
    }

    void fly_component::awake()
    {
        start_pos_ = get_owner()->get_local_position();
    }

    void fly_component::fixed_update()
    {
        if (is_flying_)
        {
            glm::vec2 curr_pos = get_owner()->get_local_position();
            if (curr_pos != end_pos_)
            {
                accu_time_ += mngn::game_time::get_instance().fixed_delta_time;
                curr_pos = glm::mix(start_pos_, end_pos_, glm::clamp(accu_time_ / fly_time_, 0.0f, 1.0f));
                get_owner()->set_local_position(curr_pos);
            }
            else
            {
                is_flying_ = false;
                accu_time_ = 0.0f;

                auto root = get_owner()->get_parent();
                auto player_states =root->get_components_in_children<player_state_component>();
                for (auto player_state : player_states)
                {
                    if (player_state->is_state<flying_state>())
                    {
                        auto player_ptr = player_state->get_owner();
                        player_ptr->set_parent(root);
                        player_state->change_state(std::make_unique<start_state>(player_ptr));
                    }
                }
            }
        }
    }

    void fly_component::fly()
    {
        is_flying_ = true;
    }
}
