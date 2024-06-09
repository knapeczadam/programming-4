#pragma once

// Project includes
#include "minigin/input/base_command.h"

namespace mngn
{
    // Forward declarations
    class game_component;
    
    class game_component_command : public base_command
    {
    public:
        explicit game_component_command(game_component *component_ptr) : game_component_ptr_(component_ptr)
        {
        }

        ~game_component_command() override = default;

        game_component_command(game_component_command const &other)            = default;
        game_component_command(game_component_command &&other)                 = default;
        game_component_command &operator=(game_component_command const &other) = default;
        game_component_command &operator=(game_component_command &&other)      = default;

    protected:
        game_component *game_component_ptr_ = nullptr;
        
    };
}
