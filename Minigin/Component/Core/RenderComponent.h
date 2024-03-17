#pragma once
#include "BaseComponent.h"

namespace dae
{
    class RenderComponent : public BaseComponent
    {
    public:
        RenderComponent() = default;
        virtual ~RenderComponent() override = default;

        RenderComponent(const RenderComponent& other)            = delete;
        RenderComponent(RenderComponent&& other)                 = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other)      = delete;
        
        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Render; }

        virtual void Render() const = 0;
    };
}
