#include "score_component.h"

namespace dae
{
    void score_component::add_score(int const score)
    {
        score_ += score;
        notify_observers("ScoreChanged");
        if (score_ >= 500 and not achievement_unlocked_)
        {
            notify_observers("AchievementUnlocked");
            achievement_unlocked_ = true;
        }
    }
}
