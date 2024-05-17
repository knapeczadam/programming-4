#pragma once
// Project includes
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class spawn_component final : public mngn::physics_component
    {
    public:
        spawn_component()           = default;
        ~spawn_component() override = default;

        spawn_component(spawn_component const &other)            = delete;
        spawn_component(spawn_component &&other)                 = delete;
        spawn_component &operator=(spawn_component const &other) = delete;
        spawn_component &operator=(spawn_component &&other)      = delete;

        void fixed_update() override;
        void spawn(glm::vec2 const &start_pos, glm::vec2 const &end_pos);

    private:
        float spawn_time_  = 2.0f;
        float accu_time_     = 0.0f;
        bool  is_spawning_ = false;
        glm::vec2 start_pos_;
        glm::vec2 end_pos_ ;
        
    };
}
