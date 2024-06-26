﻿#pragma once

// Project includes
#include "minigin/core/game_component.h"

namespace mngn
{
    class rendering_component : public game_component
    {
    public:
        rendering_component()           = default;
        ~rendering_component() override = default;

        rendering_component(rendering_component const &other)            = delete;
        rendering_component(rendering_component &&other)                 = delete;
        rendering_component &operator=(rendering_component const &other) = delete;
        rendering_component &operator=(rendering_component &&other)      = delete;

        [[nodiscard]] auto family() const -> component_family override { return component_family::rendering; }

        virtual void render() const = 0;
    };
}
