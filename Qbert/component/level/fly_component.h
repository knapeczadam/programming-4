#pragma once

// Project includes
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class fly_component final : public mngn::physics_component
    {
    public:
        fly_component()           = default;
        ~fly_component() override = default;

        fly_component(fly_component const &other)            = delete;
        fly_component(fly_component &&other)                 = delete;
        fly_component &operator=(fly_component const &other) = delete;
        fly_component &operator=(fly_component &&other)      = delete;

        void start() override;
        void fixed_update() override;
        void on_disable() override;
        
        void fly();

    private:
        float fly_time_  = 2.0f;
        float accu_time_ = 0.0f;
        bool  is_flying_ = false;
        glm::vec2 start_pos_;
        glm::vec2 end_pos_ = {224.0f, 36.0f};
    };
}
