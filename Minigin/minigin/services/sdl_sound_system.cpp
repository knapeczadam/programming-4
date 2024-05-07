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

    void sdl_sound_system::play_sound(resource_id id, int const volume)
    {
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sdl_sound_system::play_sound" << '\n';
        auto effect = resource_manager::get_instance().get_sound_effect(id);
        effect->set_volume(volume);
        // auto stream = resource_manager::get_instance().get_sound_stream(id);
        // stream->set_volume(volume);
        [[maybe_unused]] auto x = effect->play(0);
        //[[maybe_unused]] auto y = stream->play(0);
    }
}
