#include "move_component.h"

// Project includes
#include "minigin/core/game_object.h"

namespace qbert
{
    void move_component::fixed_update()
    {
        if (is_moving_)
        {
            auto const go = get_owner();
            auto const new_pos = go->get_local_position() + direction_ * speed_;
            go->set_local_position(new_pos);
        }
    }

    void move_component::set_direction(glm::vec3 const &direction)
    {
        is_moving_ = true;
        direction_ = direction;
    }
}
