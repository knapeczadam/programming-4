#include "player_health_component.h"

// Project includes
#include "core/progress_manager.h"

namespace qbert
{
    player_health_component::player_health_component(int health)
        : health_component{health}
    {
    }

    void player_health_component::on_enable()
    {
        notify_observers("update_health_display");
    }

    void player_health_component::take_damage(int damage)
    {
        progress_manager::instance().take_damage(damage);
        notify_observers("health_changed");
        notify_observers("update_health_display");
    }

    void player_health_component::heal(int health)
    {
        progress_manager::instance().heal(health);
        notify_observers("health_changed");
        notify_observers("update_health_display");
    }

    auto player_health_component::health() const -> int
    {
        return progress_manager::instance().health();
    }
}
