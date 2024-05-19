#include "level_counter_component.h"

namespace qbert
{
    void level_counter_component::start()
    {
        notify_observers("level_changed");
    }

    void level_counter_component::set_level(int level)
    {
        level_ = level;
        notify_observers("level_changed");
    }

    void level_counter_component::increase_level()
    {
        ++level_;
        notify_observers("level_changed");
    }
}
