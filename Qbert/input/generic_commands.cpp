#include "generic_commands.h"

namespace qbert
{
    void debug_command::execute()
    {
        notify_observers("debug");
    }
}
