#pragma once

// Project includes
#include "component/core/game_component.h"

namespace dae
{
    class physics_component : public game_component
    {
    public:
        physics_component()           = default;
        ~physics_component() override = default;

        physics_component(physics_component const &other)            = delete;
        physics_component(physics_component &&other)                 = delete;
        physics_component &operator=(physics_component const &other) = delete;
        physics_component &operator=(physics_component &&other)      = delete;

        [[nodiscard]] auto get_family() const -> component_family override { return component_family::physics; }
        
        virtual void fixed_update() = 0;
    };
}
