﻿#include "component_command.h"

#include "component/implementation/health_component.h"
#include "component/implementation/score_component.h"

namespace dae
{
    void damage_command::execute()
    {
        static_cast<health_component*>(get_game_component())->take_damage(damage_);
    }

    void score_command::execute()
    {
        // basically its just broadcasting a function, simpler way to call a function
        static_cast<score_component*>(get_game_component())->add_score(score_);
    }
}
