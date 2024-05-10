#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Forward declarations
namespace mngn
{
    class sprite;
    class sprite_ui_component;
}

namespace qbert
{
    class flicker_component final : public mngn::custom_component
    {
    public:
        flicker_component()           = default;
        explicit flicker_component(float delay);
        ~flicker_component() override = default;

        flicker_component(flicker_component const &other)            = delete;
        flicker_component(flicker_component &&other)                 = delete;
        flicker_component &operator=(flicker_component const &other) = delete;
        flicker_component &operator=(flicker_component &&other)      = delete;

        void awake() override;
        void update() override;

    private:
        mngn::sprite           *sprite_ptr_           = nullptr;
        mngn::sprite_ui_component *sprite_component_ptr_ = nullptr;
        float flicker_time_ = 0.4f;
        float delay_        = 0.0f;
        float accu_time_    = 0.0f;
    };
}
