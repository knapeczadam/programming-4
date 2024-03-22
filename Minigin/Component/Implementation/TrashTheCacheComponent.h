#pragma once

// Project includes
#include "UIComponent.h"

namespace dae
{
    class TrashTheCacheComponent final : public UIComponent
    {
    public:
        TrashTheCacheComponent() = default;
        virtual ~TrashTheCacheComponent() override = default;

        TrashTheCacheComponent(const TrashTheCacheComponent& other)            = delete;
        TrashTheCacheComponent(TrashTheCacheComponent&& other)                 = delete;
        TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
        TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other)      = delete;

        virtual ComponentType GetType() const override { return ComponentType::TrashTheCache; }
        virtual void RenderUI() const override;
    };
}
