#include "score_counter_component.h"

namespace qbert
{
    void score_counter_component::start()
    {
        notify_observers("score_changed");
    }

    void score_counter_component::add_score(int score)
    {
        score_ += score;
        notify_observers("score_changed");
    }
}
