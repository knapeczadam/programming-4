#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class UIComponent : public BaseComponent
    {
    public:
        UIComponent() = default;
        virtual ~UIComponent() override = default;

        UIComponent(const UIComponent& other)            = delete;
        UIComponent(UIComponent&& other)                 = delete;
        UIComponent& operator=(const UIComponent& other) = delete;
        UIComponent& operator=(UIComponent&& other)      = delete;
        
        virtual ComponentFamily GetFamily() const override { return ComponentFamily::UI; }

        virtual void RenderUI() const = 0;
    };
}
