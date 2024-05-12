#include "health_component.h"

// Project includes
#include "component/player/position_idx_component.h"

namespace qbert
{
    void health_component::awake()
    {
        notify_observers("health_changed");
    }

    void health_component::take_damage(int damage)
    {
        if (health_ <= 0)
            return;
        health_ -= damage;
        notify_observers("health_changed");
    }
}
