#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class rendering_component : public base_component
    {
    public:
        rendering_component() = default;
        ~rendering_component() override = default;

        rendering_component(const rendering_component& other)            = delete;
        rendering_component(rendering_component&& other)                 = delete;
        rendering_component& operator=(const rendering_component& other) = delete;
        rendering_component& operator=(rendering_component&& other)      = delete;

        [[nodiscard]] auto get_family() const -> component_family override { return component_family::rendering; }

        virtual void render() const = 0;
    };
}
