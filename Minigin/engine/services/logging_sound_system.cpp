﻿#include "logging_sound_system.h"

// Standard includes
#include <iostream>
#include <thread>

namespace dae
{
    void logging_sound_system::play_sound(resource_id id, int const volume)
    {
        sound_system_->play_sound(id, volume);
        std::cout << "# Thread " << std::this_thread::get_id() << ": Playing " << (int) id << " at volume " << volume << '\n';
    }
}
