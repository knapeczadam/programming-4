#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class rotator_component final : public mngn::custom_component
    {
    public:
        rotator_component()           = default;
        ~rotator_component() override = default;

        rotator_component(rotator_component const &other)            = delete;
        rotator_component(rotator_component &&other)                 = delete;
        rotator_component &operator=(rotator_component const &other) = delete;
        rotator_component &operator=(rotator_component &&other)      = delete;

        void update() override;

    private:
        float const rotation_angle_deg_ = 1.0f;
    };
}
