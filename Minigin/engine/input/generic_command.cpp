﻿#include "generic_command.h"

// Project includes
#include "achievement.h"

namespace dae
{
    void reset_achievements_command::execute()
    {
        const auto achievements = static_cast<CSteamAchievements*>(achievement_ptr_);
        achievements->ResetAchievements();
    }
}
