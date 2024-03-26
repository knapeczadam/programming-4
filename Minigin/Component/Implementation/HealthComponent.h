#pragma once

// Project includes
#include "CustomComponent.h"
#include "IObserver.h"

namespace dae
{
    class HealthComponent final : public CustomComponent, public Subject
    {
    public:
        HealthComponent() = default;
        virtual ~HealthComponent() override = default;
        
        HealthComponent(const HealthComponent& other)            = delete;
        HealthComponent(HealthComponent&& other)                 = delete;
        HealthComponent& operator=(const HealthComponent& other) = delete;
        HealthComponent& operator=(HealthComponent&& other)      = delete;

        void TakeDamage(int damage);
        auto GetHealth() const -> int { return m_Health; }

        static auto GetInitialHealth() -> int { return 3; }

    private:
        int m_Health = GetInitialHealth();
    };
}
