#include "level_counter_component.h"

// Project includes
#include "core/progress_manager.h"

namespace qbert
{
    void level_counter_component::on_enable()
    {
        notify_observers("level_changed");
    }

    void level_counter_component::start()
    {
        notify_observers("level_changed");
    }

    void level_counter_component::on_disable()
    {
        level_ = 1;
    }

    void level_counter_component::increase_level()
    {
        ++level_;
        progress_manager::instance().set_level(level_);
        notify_observers("level_changed");
    }
}
