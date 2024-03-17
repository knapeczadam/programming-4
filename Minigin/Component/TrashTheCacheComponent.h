#pragma once
#include "UIComponent.h"

namespace dae
{
    
    class TrashTheCacheComponent : public UIComponent
    {
    public:
        TrashTheCacheComponent() = default;
        ~TrashTheCacheComponent() override = default;

        TrashTheCacheComponent(const TrashTheCacheComponent& other)            = delete;
        TrashTheCacheComponent(TrashTheCacheComponent&& other)                 = delete;
        TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
        TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other)      = delete;

        ComponentType GetType() const override { return ComponentType::TrashTheCache; }
        void RenderUI() const override;
    };
}
