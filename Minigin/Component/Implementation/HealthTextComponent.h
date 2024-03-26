#pragma once
#include "IObserver.h"
#include "TextComponent.h"

namespace dae
{
    class HealthTextComponent final : public TextComponent, public IObserver
    {
    public:
        HealthTextComponent() = default;
        virtual ~HealthTextComponent() override = default;

        HealthTextComponent(const HealthTextComponent& other)            = delete;
        HealthTextComponent(HealthTextComponent&& other)                 = delete;
        HealthTextComponent& operator=(const HealthTextComponent& other) = delete;
        HealthTextComponent& operator=(HealthTextComponent&& other)      = delete;
        
        void Notify(const std::string& event, Subject* subject) override;
    };
}
