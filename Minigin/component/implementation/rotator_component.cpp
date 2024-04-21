#include "rotator_component.h"

// Project includes
#include "core/game_object.h"

namespace dae
{
    void rotator_component::update()
    {
        auto const &pos = get_owner()->get_local_position();
        float const cos_angle = glm::cos(glm::radians(rotation_angle_deg_));
        float const sin_angle = glm::sin(glm::radians(rotation_angle_deg_));
        float const new_x = pos.x * cos_angle - pos.y * sin_angle;
        float const new_y = pos.x * sin_angle + pos.y * cos_angle;
        get_owner()->set_local_position(new_x, new_y);
        // TODO: delta time?
    }
}
