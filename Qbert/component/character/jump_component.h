#pragma once

// Project includes
#include "core/freezer.h"
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    // Forward declarations
    class direction_component;
    
    class jump_component final : public mngn::physics_component, public freezer
    {
    public:
        jump_component()          = default;
        ~jump_component() override = default;

        jump_component(jump_component const &other)            = delete;
        jump_component(jump_component &&other)                 = delete;
        jump_component &operator=(jump_component const &other) = delete;
        jump_component &operator=(jump_component &&other)      = delete;
        
        void awake() override;
        void on_enable() override;
        void fixed_update() override;
        void on_disable() override;

        void jump();
        void reset();

        void set_jump_offset(float offset_x, float offset_y) { offset_x_ = offset_x; offset_y_ = offset_y; }

    private:
        void calculate_bezier_positions();

    protected:
        direction_component *direction_comp_ptr_ = nullptr;
        float jump_time_  = 0.4f;
        float accu_time_  = 0.0f;
        bool  is_jumping_ = false;

        float offset_x_ = 32.0f;
        float offset_y_ = 48.0f;
        
        glm::vec2 start_pos_  = {};
        glm::vec2 corner_pos_ = {};
        glm::vec2 pos_1_      = {};
        glm::vec2 pos_2_      = {};
        glm::vec2 end_pos_    = {};
        glm::vec2 curr_pos_   = {};
        
    };
}
