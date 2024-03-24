#include "HealthComponent.h"

namespace dae
{
    void HealthComponent::TakeDamage(int damage)
    {
        if (m_Health <= 0)
            return;
        m_Health -= damage;
        NotifyObservers("HealthChanged");
    }
}
