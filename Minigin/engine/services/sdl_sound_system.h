#pragma once

// Project includes
#include "i_sound_system.h"


namespace dae
{
    
    class sdl_sound_system final : public i_sound_system
    {
    public:
        sdl_sound_system();
        
        void play_sound(resource_id id, int const volume) override;
    };
}
