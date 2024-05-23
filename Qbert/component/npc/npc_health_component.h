#pragma once

// Project includes
#include "component/character/health_component.h"

namespace qbert
{
    class npc_health_component final : public health_component
    {
    public:
        npc_health_component()           = default;
        explicit npc_health_component(int health);
        ~npc_health_component() override = default;

        npc_health_component(npc_health_component const &other)            = delete;
        npc_health_component(npc_health_component &&other)                 = delete;
        npc_health_component &operator=(npc_health_component const &other) = delete;
        npc_health_component &operator=(npc_health_component &&other)      = delete;
        
        void on_disable() override;
    };
}
