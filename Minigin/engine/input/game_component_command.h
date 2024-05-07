#pragma once

// Project includes
#include "base_command.h"

namespace dae
{
    // Forward declarations
    class game_component;
    
    class game_component_command : public base_command
    {
    public:
        explicit game_component_command(game_component *component_ptr) : component_ptr_(component_ptr)
        {
        }

        ~game_component_command() override = default;

        game_component_command(game_component_command const &other)            = default;
        game_component_command(game_component_command &&other)                 = default;
        game_component_command &operator=(game_component_command const &other) = default;
        game_component_command &operator=(game_component_command &&other)      = default;

    protected:
        [[nodiscard]] auto get_game_component() const -> game_component * { return component_ptr_; }

    private:
        game_component *component_ptr_;
        
    };
}
