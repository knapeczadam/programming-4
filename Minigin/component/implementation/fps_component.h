#pragma once

// Project includes
#include "text_component.h"

namespace dae
{
    class fps_component final : public text_component
    {
    public:
        fps_component()           = default;
        ~fps_component() override = default;

        fps_component(fps_component const &other)            = delete;
        fps_component(fps_component &&other)                 = delete;
        fps_component &operator=(fps_component const &other) = delete;
        fps_component &operator=(fps_component &&other)      = delete;

        void update() override;
    };
}
