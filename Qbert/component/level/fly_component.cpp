#include "fly_component.h"

// Project includes
#include "minigin/core/game_time.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    fly_component::fly_component(glm::vec2 start_pos)
        : start_pos_(start_pos)
    {
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
                notify_observers("fly_finished");
            }
        }
    }

    void fly_component::notify(std::string const &event, [[maybe_unused]] mngn::subject *subject_ptr)
    {
        if (event == "jump_started")
        {
            is_flying_ = true;
        }
    }
}
