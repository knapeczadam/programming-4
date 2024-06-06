#include "player_health_component.h"

// Project includes
#include "core/progress_manager.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    player_health_component::player_health_component(int health)
        : health_component{health}
    {
    }

    void player_health_component::on_enable()
    {
        progress_manager::instance().set_health(owner()->name(), original_health_);
        notify_observers("update_health_display");
    }

    void player_health_component::take_damage(int damage)
    {
        progress_manager::instance().take_damage(owner()->name(), damage);
        notify_observers("health_decreased");
        notify_observers("update_health_display");
    }

    void player_health_component::heal(int health)
    {
        progress_manager::instance().heal(owner()->name(), health);
        notify_observers("update_health_display");
    }

    auto player_health_component::health() const -> int
    {
        return progress_manager::instance().health(owner()->name());
    }
}
