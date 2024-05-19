#include "health_component.h"

namespace qbert
{
    health_component::health_component(int health)
        : health_{health}
        , original_health_{health}
    {
    }

    void health_component::on_enable()
    {
        notify_observers("health_changed");
    }

    void health_component::on_disable()
    {
        health_ = original_health_;
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
