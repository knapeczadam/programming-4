#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class CustomComponent : public BaseComponent
    {
    public:
        CustomComponent() = default;
        virtual ~CustomComponent() override = default;

        CustomComponent(const CustomComponent& other)            = delete;
        CustomComponent(CustomComponent&& other)                 = delete;
        CustomComponent& operator=(const CustomComponent& other) = delete;
        CustomComponent& operator=(CustomComponent&& other)      = delete;

        ComponentFamily GetFamily() const override { return ComponentFamily::Custom; }
    };
}
