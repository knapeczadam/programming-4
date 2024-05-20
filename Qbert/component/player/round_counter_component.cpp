#include "round_counter_component.h"

// Project includes
#include "core/progress_manager.h"

namespace qbert
{
    void round_counter_component::on_enable()
    {
        notify_observers("round_changed");
    }

    void round_counter_component::start()
    {
        notify_observers("round_changed");
    }

    void round_counter_component::on_disable()
    {
        round_ = 1;
    }

    void round_counter_component::increase_round()
    {
        ++round_;
        if (round_ == 5)
        {
            round_ = 1;
        }
        progress_manager::instance().set_level(round_);
        notify_observers("round_changed");
    }
}
