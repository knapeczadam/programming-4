#include "HealthComponent.h"

namespace dae
{
    void health_component::take_damage(const int damage)
    {
        if (health_ <= 0)
            return;
        health_ -= damage;
        notify_observers("HealthChanged");
    }
}
