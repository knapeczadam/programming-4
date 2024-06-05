#pragma once

// Project includes
#include "minigin/services/sound_system.h"

namespace mngn
{
    class sdl_sound_system final : public sound_system
    {
    public:
        sdl_sound_system();

    protected:
        void play_sound_impl(int id, int volume) override;
    };
}
