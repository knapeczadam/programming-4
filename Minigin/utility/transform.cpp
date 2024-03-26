#include "transform.h"

namespace dae
{
    void transform::set_world_position(const float x, const float y)
    {
        set_world_position(glm::vec3{ x, y, world_position_.z });
    }

    void transform::set_world_position(const float x, const float y, const float z)
    {
        set_world_position(glm::vec3{ x, y, z });
    }

    void transform::set_world_position(const glm::vec2& position)
    {
        set_world_position(glm::vec3{ position, world_position_.z });
    }

    void transform::set_world_position(const glm::vec3& position)
    {
        world_position_ = position;
    }

    void transform::set_local_position(const float x, const float y)
    {
        set_local_position(glm::vec3{ x, y, local_position_.z });
    }

    void transform::set_local_position(const float x, const float y, const float z)
    {
        set_local_position(glm::vec3{ x, y, z });
    }

    void transform::set_local_position(const glm::vec2& position)
    {
        set_local_position(glm::vec3{ position, local_position_.z });
    }

    void transform::set_local_position(const glm::vec3& position)
    {
        local_position_ = position;
    }
}
