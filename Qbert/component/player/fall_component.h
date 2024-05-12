#pragma once

// Project includes
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class fall_component final : public mngn::physics_component
    {
    public:
        fall_component()           = default;
        ~fall_component() override = default;

        fall_component(fall_component const &other) = delete;
        fall_component(fall_component &&other) noexcept = delete;
        fall_component &operator=(fall_component const &other) = delete;
        fall_component &operator=(fall_component &&other) noexcept = delete;

        void fixed_update() override;

        void fall(int col_idx);

    private:
        void calculate_bezier_positions(int col_idx);

    private:
        float fall_time_  = 1.0f;
        float accu_time_  = 0.0f;
        bool  is_falling_ = false;
        
        glm::vec2 start_pos_  = {};
        glm::vec2 corner_pos_ = {};
        glm::vec2 pos_1_      = {};
        glm::vec2 pos_2_      = {};
        glm::vec2 end_pos_    = {0.0f, 512.0f};
        glm::vec2 curr_pos_   = {};
    };
}
