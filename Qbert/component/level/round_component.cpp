#include "round_component.h"

namespace qbert
{
    void round_component::awake()
    {
        notify_observers("round_changed");
    }

    void round_component::set_round(int round)
    {
        round_ = round;
        notify_observers("round_changed");
    }

    void round_component::increase_round()
    {
        ++round_;
        notify_observers("round_changed");
    }
}
