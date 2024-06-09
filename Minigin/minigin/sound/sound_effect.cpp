#include "sound_effect.h"

// Standard includes
#include <iostream>
#include <thread>

// SDL includes
#pragma comment(lib, "SDL2_mixer.lib")

namespace mngn
{
    sound_effect::sound_effect(std::string const &path)
        : mix_chunk_ptr_{Mix_LoadWAV(path.c_str())}
    {
        if (mix_chunk_ptr_ == nullptr)
        {
            std::cerr << "sound_effect: Failed to load " << path << ",\nSDL_mixer error: " << Mix_GetError() << '\n';
        }
    }

    sound_effect::~sound_effect()
    {
        Mix_FreeChunk(mix_chunk_ptr_);
    }

    auto sound_effect::is_loaded() const -> bool
    {
        return mix_chunk_ptr_ != nullptr;
    }

    auto sound_effect::play(int const loops) const -> bool
    {
        std::cout << '#' << std::this_thread::get_id() << " thread: calling sound_effect::play" << '\n';
        // Don't save the channel as a data member,
        // because when it stops playing the channel becomes free
        // and available for usage by other effects
        if (mix_chunk_ptr_)
        {
            int const channel = Mix_PlayChannel(-1, mix_chunk_ptr_, loops);
            return channel != -1;
        }
        return false;
    }
    
    auto sound_effect::volume() const -> int
    {
        if (mix_chunk_ptr_)
        {
            return Mix_VolumeChunk(mix_chunk_ptr_, -1);
        }
        return -1;
    }


    void sound_effect::set_volume(int const value)
    {
        if (mix_chunk_ptr_)
        {
            Mix_VolumeChunk(mix_chunk_ptr_, value);
        }
    }

    void sound_effect::stop_all()
    {
        Mix_HaltChannel(-1);
    }

    void sound_effect::pause_all()
    {
        Mix_Pause(-1);
    }

    void sound_effect::resume_all()
    {
        Mix_Resume(-1);
    }
}
