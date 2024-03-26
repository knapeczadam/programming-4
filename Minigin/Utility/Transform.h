#pragma once

// GLM includes
#include <glm/glm.hpp>

namespace dae
{
    class transform final
    {
    public:
        auto get_world_position() const -> const glm::vec3& { return world_position_; }
        auto get_local_position() const -> const glm::vec3& { return local_position_; }
        
        void set_world_position(float x, float y);
        void set_world_position(float x, float y, float z);
        void set_world_position(const glm::vec2& position);
        void set_world_position(const glm::vec3& position);

        void set_local_position(float x, float y);
        void set_local_position(float x, float y, float z);
        void set_local_position(const glm::vec2& position);
        void set_local_position(const glm::vec3& position);

    private:
        glm::vec3 world_position_ = {};
        glm::vec3 local_position_ = {};
    };
}
