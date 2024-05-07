#include "health_component.h"

namespace qbert
{
    void health_component::take_damage(int const damage)
    {
        if (health_ <= 0)
            return;
        health_ -= damage;
        notify_observers("HealthChanged");
    }
}
