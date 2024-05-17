#pragma once

// Project includes
#include "state/character/character_state.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    class npc_spawning_state final : public character_state
    {
    public:
        explicit npc_spawning_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void update() override;
        void on_exit() override;

        void set_positions();
        void set_sprite();
        

    private:
        float     spawn_time_ = 2.0f;
        float     accu_time_  = 0.0f;
        glm::vec2 start_pos_  = {};
        glm::vec2 end_pos_    = {};
    };
}
