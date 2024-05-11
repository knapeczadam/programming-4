#pragma once

// Project includes
#include "minigin/component/family/physics_component.h"
#include "input/game_object_commands.h"

// GLM includes
#include <glm/glm.hpp>


namespace qbert
{
    class fly_component final : public mngn::physics_component, public mngn::subject, public mngn::i_observer
    {
    public:
        fly_component()           = default;
        explicit fly_component(glm::vec2 start_pos);
        ~fly_component() override = default;

        fly_component(fly_component const &other)            = delete;
        fly_component(fly_component &&other)                 = delete;
        fly_component &operator=(fly_component const &other) = delete;
        fly_component &operator=(fly_component &&other)      = delete;

        void fixed_update() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        float fly_time_  = 2.0f;
        float accu_time_ = 0.0f;
        bool  is_flying_ = false;
        glm::vec2 start_pos_;
        glm::vec2 end_pos_ = {224.0f, 36.0f};
    };
}
