#include "ScoreComponent.h"

// Project includes
#include "Achievement.h"

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
