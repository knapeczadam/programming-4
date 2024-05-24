#include "sdl_sound_system.h"

// Project includes
#include "minigin/core/resource_manager.h"
#include "minigin/sound/sound_effect.h"
#include "minigin/sound/sound_stream.h"

// SDL includes
#include <SDL_mixer.h>

// Standard includes
#include <iostream>
#include <thread>

#include "minigin/sound/sound_manager.h"

namespace mngn
{
    sdl_sound_system::sdl_sound_system()
    {
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sdl_sound_system::sdl_sound_system" << '\n';
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "minigin: error when calling Mix_OpenAudio: " << Mix_GetError() << '\n';
        }
    }

    void sdl_sound_system::play_sound(int id, int volume)
    {
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sdl_sound_system::play_sound" << '\n';
        sound_manager::instance().play_sound(id, volume);
    }
}
