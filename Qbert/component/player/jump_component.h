﻿#pragma once

// Project includes
#include "minigin/component/family/physics_component.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class jump_component final : public mngn::physics_component, public mngn::subject
    {
    public:
        jump_component()           = default;
        ~jump_component() override = default;

        jump_component(jump_component const &other)            = delete;
        jump_component(jump_component &&other)                 = delete;
        jump_component &operator=(jump_component const &other) = delete;
        jump_component &operator=(jump_component &&other)      = delete;

        void fixed_update() override;
        void jump(int row_dir, int col_dir);

        [[nodiscard]] auto get_row_direction() const -> int { return row_dir_; }
        [[nodiscard]] auto get_col_direction() const -> int { return col_dir_; }
        
    private:
        void calculate_bezier_positions(int row_dir, int col_dir);

    private:
        float jump_time_  = 0.5f;
        float accu_time_  = 0.0f;
        int   row_dir_    = 0;
        int   col_dir_    = 0;
        bool  is_jumping_ = false;
        
        glm::vec2 start_pos_  = {};
        glm::vec2 corner_pos_ = {};
        glm::vec2 pos_1_      = {};
        glm::vec2 pos_2_      = {};
        glm::vec2 end_pos_    = {};
        glm::vec2 curr_pos_   = {};
    };
}
