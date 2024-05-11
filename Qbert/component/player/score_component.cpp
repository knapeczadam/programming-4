#include "score_component.h"

namespace qbert
{
    void score_component::awake()
    {
        notify_observers("score_changed");
    }

    void score_component::add_score(int score)
    {
        score_ += score;
        notify_observers("score_changed");
    }
}
