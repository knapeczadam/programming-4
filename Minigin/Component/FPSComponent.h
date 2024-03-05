#pragma once
#include "TextComponent.h"

namespace dae
{
    class FPSComponent final : public TextComponent
    {
    public:
        FPSComponent(std::shared_ptr<Font> font);
        ~FPSComponent() override = default;

        FPSComponent(const FPSComponent& other)            = delete;
        FPSComponent(FPSComponent&& other)                 = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other)      = delete;

        void Update() override;
    };
}
