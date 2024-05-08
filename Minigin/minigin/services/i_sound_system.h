#pragma once

namespace mngn
{
    class i_sound_system 
    {
    public:
        virtual ~i_sound_system() = default;

        virtual void play_sound(int id, int const volume = 1) = 0;
    };
}
