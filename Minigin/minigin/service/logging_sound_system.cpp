#include "logging_sound_system.h"

// Standard includes
#include <iostream>
#include <thread>

namespace mngn
{
    void logging_sound_system::play_sound_impl(int id, int volume)
    {
        sound_system_->play_sound(id, volume);
        std::cout << '#' << std::this_thread::get_id() << " thread: playing " << id << " at volume " << volume << '\n';
    }
}
