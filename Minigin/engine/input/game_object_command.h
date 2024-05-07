﻿#pragma once

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
        explicit game_object_command(game_object *game_object_ptr) : game_object_ptr_{game_object_ptr}
        {
        }

        ~game_object_command() override = default;

        game_object_command(game_object_command const &other)            = default;
        game_object_command(game_object_command &&other)                 = default;
        game_object_command &operator=(game_object_command const &other) = default;
        game_object_command &operator=(game_object_command &&other)      = default;

    protected:
        [[nodiscard]] auto get_game_object() const -> game_object * { return game_object_ptr_; }

    private:
        game_object *game_object_ptr_ = nullptr;
    };
}
