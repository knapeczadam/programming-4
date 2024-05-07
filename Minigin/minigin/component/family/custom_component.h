#pragma once

// Project includes
#include "minigin/core/game_component.h"

namespace mngn
{
    class custom_component : public game_component
    {
    public:
        custom_component()           = default;
        ~custom_component() override = default;

        custom_component(custom_component const &other)            = delete;
        custom_component(custom_component &&other)                 = delete;
        custom_component &operator=(custom_component const &other) = delete;
        custom_component &operator=(custom_component &&other)      = delete;

        [[nodiscard]] auto get_family() const -> component_family override { return component_family::custom; }
    };
}
