#include "rotator_component.h"

// Project includes
#include "game_object.h"

namespace dae
{
    void rotator_component::update()
    {
        const auto& pos = get_owner()->get_local_position();
        const float cos_angle = glm::cos(glm::radians(rotation_angle_deg_));
        const float sin_angle = glm::sin(glm::radians(rotation_angle_deg_));
        const float new_x = pos.x * cos_angle - pos.y * sin_angle;
        const float new_y = pos.x * sin_angle + pos.y * cos_angle;
        get_owner()->set_local_position(new_x, new_y);
        // TODO: delta time?
    }
}
