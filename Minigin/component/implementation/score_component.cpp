#include "score_component.h"

namespace dae
{
    void score_component::add_score(int score)
    {
        score_ += score;
        notify_observers("ScoreChanged");
        if (score_ >= 500)
        {
            notify_observers("AchievementUnlocked");
        }
    }
}
