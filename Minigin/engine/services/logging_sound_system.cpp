#include "logging_sound_system.h"

// Standard includes
#include <iostream>

namespace dae
{
    void logging_sound_system::play_sound(sound_id const id, float const volume) const
    {
        sound_system_->play_sound(id, volume);
        std::cout << "Playing " << id << " at volume " << volume << '\n';
    }
}
