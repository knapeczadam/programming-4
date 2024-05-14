#include "round_counter_component.h"

namespace qbert
{
    void round_counter_component::awake()
    {
        notify_observers("round_changed");
    }

    void round_counter_component::set_round(int round)
    {
        round_ = round;
        notify_observers("round_changed");
    }

    void round_counter_component::increase_round()
    {
        ++round_;
        notify_observers("round_changed");
    }
}
