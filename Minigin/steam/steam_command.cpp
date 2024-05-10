#include "steam_command.h"

// Project includes
#include "steam/achievement.h"

namespace steam
{
    void reset_achievements_command::execute()
    {
        auto const achievements = static_cast<steam::steam_achievements*>(achievement_ptr_);
        achievements->reset_achievements();
    }
}
