#include "health_component.h"

namespace qbert
{
    void health_component::start()
    {
        notify_observers("health_changed");
    }

    void health_component::take_damage(int damage)
    {
        if (damage <= 0)
            return;
        health_ -= damage;
        notify_observers("health_changed");
    }

    void health_component::heal(int health)
    {
        if (health <= 0)
            return;
        health_ += health;
    }
}
