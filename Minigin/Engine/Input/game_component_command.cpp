#include "game_component_command.h"

#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
    void damage_command::execute()
    {
        static_cast<health_component*>(get_game_component())->take_damage(damage_);
    }

    void score_command::execute()
    {
        static_cast<score_component*>(get_game_component())->add_score(score_);
    }
}
