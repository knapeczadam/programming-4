#include "level_counter_component.h"

// Project includes
#include "core/progress_manager.h"

namespace qbert
{
    void level_counter_component::on_enable()
    {
        notify_observers("update_level_display");
    }

    void level_counter_component::start()
    {
        notify_observers("update_level_display");
    }

    auto level_counter_component::level() const -> int
    {
        return progress_manager::instance().level();
    }

    void level_counter_component::increase_level()
    {
        progress_manager::instance().increase_level();
        notify_observers("update_level_display");
    }
}
