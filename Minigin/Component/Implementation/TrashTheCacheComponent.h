#pragma once

// Project includes
#include "UIComponent.h"

namespace dae
{
    class TrashTheCacheComponent : public UIComponent
    {
    public:
        TrashTheCacheComponent() = default;
        virtual ~TrashTheCacheComponent() override = default;

        TrashTheCacheComponent(const TrashTheCacheComponent& other)            = delete;
        TrashTheCacheComponent(TrashTheCacheComponent&& other)                 = delete;
        TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
        TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other)      = delete;

        virtual ComponentType GetType() const override { return ComponentType::TrashTheCache; }
        void RenderUI() const override;
    };
}
