#pragma once

// Project includes
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class move_component final : public mngn::physics_component
    {
    public:
        move_component()           = default;
        ~move_component() override = default;

        move_component(move_component const &other)            = delete;
        move_component(move_component &&other)                 = delete;
        move_component &operator=(move_component const &other) = delete;
        move_component &operator=(move_component &&other)      = delete;

        void fixed_update() override;
        void set_direction(glm::vec3 const &direction);
        void stop_moving() { is_moving_ = false; }

    private:
        bool is_moving_     = false;
        float speed_         = 1.0f;
        glm::vec3 direction_ = {0.0f, 0.0f, 0.0f};
    };
}
