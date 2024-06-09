#pragma once

// Project includes
#include "core/freezer.h"
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class spawn_component final : public mngn::physics_component, public freezer
    {
    public:
        spawn_component() = default;
        spawn_component(float spawn_time_min, float spawn_time_max);
        ~spawn_component() override = default;

        spawn_component(spawn_component const &other)            = delete;
        spawn_component(spawn_component &&other)                 = delete;
        spawn_component &operator=(spawn_component const &other) = delete;
        spawn_component &operator=(spawn_component &&other)      = delete;

        void fixed_update() override;
        void on_disable() override;
        
        void spawn(glm::vec2 const &start_pos, glm::vec2 const &end_pos);

        [[nodiscard]] auto spawn_time_min() const -> float { return spawn_time_min_; }
        [[nodiscard]] auto spawn_time_max() const -> float { return spawn_time_max_; }

    private:
        float     spawn_time_     = 2.0f;
        float     spawn_time_min_ = 1.0f;
        float     spawn_time_max_ = 5.0f;
        float     accu_time_      = 0.0f;
        bool      is_spawning_    = false;
        glm::vec2 start_pos_      = {};
        glm::vec2 end_pos_        = {};
        
    };
}
