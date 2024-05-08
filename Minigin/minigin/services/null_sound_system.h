#pragma once

// Project includes
#include "i_sound_system.h"

namespace mngn
{
    class null_sound_system final : public i_sound_system
    {
    public:
        ~null_sound_system() override = default;
        
        void play_sound([[maybe_unused]] int id, [[maybe_unused]] int const volume) override { }
    };
}