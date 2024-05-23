#include "npc_health_component.h"

namespace qbert
{
    npc_health_component::npc_health_component(int health)
        : health_component{health}
    {
    }

    void npc_health_component::on_disable()
    {
        health_ = original_health_;
    }
}
