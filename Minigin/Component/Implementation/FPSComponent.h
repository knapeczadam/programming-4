#pragma once

// Project includes
#include "TextComponent.h"

namespace dae
{
    class FPSComponent final : public TextComponent
    {
    public:
        FPSComponent() = default;
        FPSComponent(std::shared_ptr<Font> font);
        virtual ~FPSComponent() override = default;

        FPSComponent(const FPSComponent& other)            = delete;
        FPSComponent(FPSComponent&& other)                 = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other)      = delete;

        void Update() override;
        
        virtual ComponentType GetType() const override { return ComponentType::FPS; }
    };
}
