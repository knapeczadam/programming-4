#include "round_counter_component.h"

// Project includes
#include "core/progress_manager.h"

namespace qbert
{
    void round_counter_component::on_enable()
    {
        notify_observers("update_round_display");
    }

    void round_counter_component::start()
    {
        notify_observers("update_round_display");
    }

    auto round_counter_component::round() const -> int
    {
        return progress_manager::instance().round();
    }

    void round_counter_component::increase_round()
    {
        progress_manager::instance().increase_round();
        notify_observers("update_round_display");
    }

    void round_counter_component::set_round(int round)
    {
        progress_manager::instance().set_round(round);
    }
}
