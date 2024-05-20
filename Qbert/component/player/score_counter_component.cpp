#include "score_counter_component.h"

#include "core/progress_manager.h"

namespace qbert
{
    void score_counter_component::on_enable()
    {
        notify_observers("score_changed");
    }

    void score_counter_component::start()
    {
        notify_observers("score_changed");
    }

    void score_counter_component::on_disable()
    {
        score_ = 0;
    }

    void score_counter_component::add_score(int score)
    {
        score_ += score;
        progress_manager::instance().add_score(score);
        notify_observers("score_changed");
    }

    auto score_counter_component::score() const -> int
    {
        return progress_manager::instance().score();
    }
}
