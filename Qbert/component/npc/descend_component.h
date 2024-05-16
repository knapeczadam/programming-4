#pragma once
// Project includes
#include "minigin/component/family/physics_component.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class descend_component final : public mngn::physics_component
    {
    public:
        descend_component()           = default;
        ~descend_component() override = default;

        descend_component(descend_component const &other)            = delete;
        descend_component(descend_component &&other)                 = delete;
        descend_component &operator=(descend_component const &other) = delete;
        descend_component &operator=(descend_component &&other)      = delete;

        void fixed_update() override;
        void descend(glm::vec2 const &start_pos, glm::vec2 const &end_pos);

    private:
        float descend_time_  = 2.0f;
        float accu_time_     = 0.0f;
        bool  is_descending_ = false;
        glm::vec2 start_pos_;
        glm::vec2 end_pos_ ;
        
    };
}
