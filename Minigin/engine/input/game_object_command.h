#pragma once

// Project includes
#include "base_command.h"

// GLM includes
#include <glm/glm.hpp>

namespace dae
{
    // Forward declarations
    class game_object;
    
    class game_object_command : public base_command
    {
    public:
        explicit game_object_command(game_object *game_object_ptr) : game_object_ptr_(game_object_ptr)
        {
        }

        ~game_object_command() override = default;

        game_object_command(game_object_command const &other)            = delete;
        game_object_command(game_object_command &&other)                 = delete;
        game_object_command &operator=(game_object_command const &other) = delete;
        game_object_command &operator=(game_object_command &&other)      = delete;

    protected:
        [[nodiscard]] auto get_game_actor() const -> game_object * { return game_object_ptr_; }

    private:
        game_object *game_object_ptr_ = nullptr;
    };

    // MoveCommand
    class move_command final : public game_object_command
    {
    public:
        move_command(game_object *game_object_ptr, glm::vec3 const &direction)
            : game_object_command(game_object_ptr)
            , direction_(direction)
        {
        }

        move_command(game_object *game_object_ptr, glm::vec2 const &direction)
            : game_object_command(game_object_ptr)
            , direction_(glm::vec3(direction, 0.0f))
        {
        }
        
        void execute() override;

    private:
        glm::vec3 direction_ = {1.0f, 0.0f, 0.0f};
        float speed_         = 1.0f;
    };
}
