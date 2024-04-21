#include "generic_command.h"

// Project includes
#include "steam/achievement.h"

namespace dae
{
    void reset_achievements_command::execute()
    {
        auto const achievements = static_cast<steam_achievements*>(achievement_ptr_);
        achievements->reset_achievements();
    }
}
