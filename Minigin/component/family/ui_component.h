#pragma once

// Project includes
#include "base_component.h"

namespace dae
{
    class ui_component : public base_component
    {
    public:
        ui_component() = default;
        ~ui_component() override = default;

        ui_component(const ui_component& other)            = delete;
        ui_component(ui_component&& other)                 = delete;
        ui_component& operator=(const ui_component& other) = delete;
        ui_component& operator=(ui_component&& other)      = delete;

        [[nodiscard]] auto get_family() const -> component_family override { return component_family::ui; }

        virtual void render_ui() const = 0;
    };
}
