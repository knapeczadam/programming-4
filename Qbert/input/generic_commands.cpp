#include "generic_commands.h"

#include "component/level/level_counter_component.h"
#include "component/level/round_counter_component.h"

namespace qbert
{
    debug_command::debug_command(void *debug_ptr)
        : debug_ptr_(debug_ptr)
    {
    }

    void debug_command::execute()
    {
        notify_observers("debug");
        auto level_comp_ptr = static_cast<round_counter_component *>(debug_ptr_);
        level_comp_ptr->increase_round();
    }
}
