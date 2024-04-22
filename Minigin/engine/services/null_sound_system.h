#pragma once

// Project includes
#include "i_sound_system.h"

namespace dae
{
    class null_sound_system final : public i_sound_system
    {
    public:
        ~null_sound_system() override = default;
        
        void play_sound([[maybe_unused]] sound_id const id, [[maybe_unused]] float const volume) const override { }
    };
}