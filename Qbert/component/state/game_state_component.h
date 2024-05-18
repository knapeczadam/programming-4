#pragma once

// Project includes
#include "component/state/state_component.h"

namespace qbert
{
    // Forward declarations
    class scene;
    
    class game_state_component final : public state_component
    {
    public:
        game_state_component();
        ~game_state_component() override = default;

        game_state_component(game_state_component const &other)            = delete;
        game_state_component(game_state_component &&other)                 = delete;
        game_state_component &operator=(game_state_component const &other) = delete;
        game_state_component &operator=(game_state_component &&other)      = delete;
    };
}
