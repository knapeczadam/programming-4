#include "level_component.h"

namespace qbert
{
    void level_component::awake()
    {
        notify_observers("level_changed");
    }

    void level_component::set_level(int level)
    {
        level_ = level;
        notify_observers("level_changed");
    }

    void level_component::increase_level()
    {
        ++level_;
        notify_observers("level_changed");
    }
}
