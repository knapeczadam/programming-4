#pragma once

// Standard includes
#include <string>

// SDL includes
#include <SDL_mixer.h>

namespace mngn
{
    class sound_effect final
    {
    public:
        explicit sound_effect(std::string const &path);
        ~sound_effect();
        
        sound_effect(sound_effect const &other)            = delete;
        sound_effect(sound_effect &&other)                 = delete;
        sound_effect &operator=(sound_effect const &other) = delete;
        sound_effect &operator=(sound_effect &&other)      = delete;

        [[nodiscard]] auto is_loaded() const -> bool;
        auto play(int const loops) const -> bool;
        [[nodiscard]] auto get_volume() const -> int;
        void set_volume(int const value);

        static void stop_all();
        static void pause_all();
        static void resume_all();

    private:
        Mix_Chunk *mix_chunk_ptr_;
    };
}
