#include "sound_stream.h"

// Standard includes
#include <iostream>

// SDL includes
#pragma comment(lib, "SDL2_mixer.lib")

namespace dae
{
    sound_stream::sound_stream(std::string const &path)
        : mix_music_ptr_{Mix_LoadMUS(path.c_str())}
    {
        if (mix_music_ptr_ == nullptr)
        {
            std::cerr << "sound_stream: Failed to load " << path << ",\nSDL_mixer error: " << Mix_GetError() << '\n'; 
        }
    }

    sound_stream::~sound_stream()
    {
        Mix_FreeMusic(mix_music_ptr_);
    }

    auto sound_stream::is_loaded() const -> bool
    {
        return mix_music_ptr_ != nullptr;
    }

    auto sound_stream::play(bool repeat) const -> bool
    {
        if (mix_music_ptr_)
        {
            int const result = Mix_PlayMusic(mix_music_ptr_, repeat ? -1 : 1);
            return result == 0;
        }
        return false;
    }

    void sound_stream::stop()
    {
        Mix_HaltMusic();
    }

    void sound_stream::pause()
    {
        Mix_PauseMusic();
    }

    void sound_stream::resume()
    {
        Mix_ResumeMusic();
    }
    
    auto sound_stream::get_volume() -> int
    {
        return Mix_VolumeMusic(-1);
    }

    void sound_stream::set_volume(int value)
    {
        Mix_VolumeMusic(value);
    }

    auto sound_stream::is_playing() -> bool
    {
        return Mix_PlayingMusic() != 0;
    }
}
