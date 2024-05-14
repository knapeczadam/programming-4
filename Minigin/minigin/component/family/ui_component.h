#pragma once

// Project includes
#include "minigin/core/game_component.h"

namespace mngn
{
    class ui_component : public game_component
    {
    public:
        ui_component()           = default;
        ~ui_component() override = default;

        ui_component(ui_component const &other)            = delete;
        ui_component(ui_component &&other)                 = delete;
        ui_component &operator=(ui_component const &other) = delete;
        ui_component &operator=(ui_component &&other)      = delete;

        [[nodiscard]] auto family() const -> component_family override { return component_family::ui; }

        virtual void render_ui() const = 0;
    };
}
