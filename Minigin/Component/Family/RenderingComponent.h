#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class RenderingComponent : public BaseComponent
    {
    public:
        RenderingComponent() = default;
        virtual ~RenderingComponent() override = default;

        RenderingComponent(const RenderingComponent& other)            = delete;
        RenderingComponent(RenderingComponent&& other)                 = delete;
        RenderingComponent& operator=(const RenderingComponent& other) = delete;
        RenderingComponent& operator=(RenderingComponent&& other)      = delete;
        
        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Rendering; }

        virtual void Render() const = 0;
    };
}
