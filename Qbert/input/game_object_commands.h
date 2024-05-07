#pragma once

// Project includes
#include "minigin/input/game_object_command.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    // Move command
    class move_command final : public mngn::game_object_command
    {
    public:
        move_command(mngn::game_object *game_object_ptr, glm::vec3 const &direction)
            : game_object_command{game_object_ptr}
            , direction_{direction}
        {
        }

        move_command(mngn::game_object *game_object_ptr, glm::vec2 const &direction)
            : game_object_command{game_object_ptr}
            , direction_{glm::vec3{direction, 0.0f}}
        {
        }
        
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<move_command>(*this);
        }

    private:
        glm::vec3 direction_ = {1.0f, 0.0f, 0.0f};
        float speed_         = 1.0f;
    };

    // Reset move command
    class reset_move_command final : public mngn::game_object_command
    {
    public:
        reset_move_command(mngn::game_object *game_object_ptr)
            : game_object_command{game_object_ptr}
        {
        }
        
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<reset_move_command>(*this);
        }
    };
    
}
