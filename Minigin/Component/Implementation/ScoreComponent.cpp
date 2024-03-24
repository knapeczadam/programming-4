#include "ScoreComponent.h"

// Project includes
#include "Achievement.h"

namespace dae
{
    void ScoreComponent::AddScore(int score)
    {
        m_Score += score;
        NotifyObservers("ScoreChanged");
        if (m_Score >= 500)
        {
	        g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
        }
    }
}
