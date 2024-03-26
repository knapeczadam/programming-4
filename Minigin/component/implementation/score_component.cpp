#include "score_component.h"

// Project includes
#include "achievement.h"

namespace dae
{
    void score_component::add_score(int score)
    {
        score_ += score;
        notify_observers("ScoreChanged");
        if (score_ >= 500)
        {
	        g_steam_achievements->SetAchievement("ACH_WIN_ONE_GAME");
        }
    }
}
