#pragma once

// Project includes
#include "custom_component.h"

namespace dae
{
    class rotator_component final : public custom_component
    {
    public:
        rotator_component() = default;
        ~rotator_component() override = default;

        rotator_component(const rotator_component& other) = delete;
        rotator_component(rotator_component&& other) = delete;
        rotator_component& operator=(const rotator_component& other) = delete;
        rotator_component& operator=(rotator_component&& other) = delete;

        void update() override;

    private:
        const float rotation_angle_deg_ = 1.0f;
        
    };
}
