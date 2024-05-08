#pragma once

// Standard includes
#include <string>

// SDL includes
#include <SDL_mixer.h>

namespace mngn
{
    class sound_stream final
    {
    public:
        explicit sound_stream(std::string const &path);
        ~sound_stream();

        sound_stream(sound_stream const &other)            = delete;
        sound_stream(sound_stream &&other)                 = delete;
        sound_stream &operator=(sound_stream const &other) = delete;
        sound_stream &operator=(sound_stream &&other)      = delete;

        [[nodiscard]] auto is_loaded() const -> bool;
        auto play(bool repeat) const -> bool;

        static void stop();
        static void pause();
        static void resume();
        static auto get_volume() -> int;
        static void set_volume(int value);
        static auto is_playing() -> bool;

    private:
        Mix_Music *mix_music_ptr_;
    };
}
