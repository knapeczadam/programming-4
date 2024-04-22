#pragma once

// Project includes
#include "i_sound_system.h"


namespace dae
{
    class sdl_sound_system final : public i_sound_system
    {
    public:
        virtual
        void play_sound(sound_id const id, float const volume) const override;
    };
}
