#pragma once

// Project includes
#include "core/freezer.h"
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class fall_component final : public mngn::physics_component, public freezer
    {
    public:
        fall_component()           = default;
        ~fall_component() override = default;

        fall_component(fall_component const &other) = delete;
        fall_component(fall_component &&other) noexcept = delete;
        fall_component &operator=(fall_component const &other) = delete;
        fall_component &operator=(fall_component &&other) noexcept = delete;

        void fixed_update() override;

        void fall(int row_dir, int col_dir, int row_idx, int col_idx);

    private:
        void calculate_bezier_positions(int row_dir, int col_dir, int row_idx, int col_idx);

    private:
        float const fall_time_  = 1.52f;
        float const total_time_ = 2.5f;
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
