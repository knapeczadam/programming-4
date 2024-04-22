#pragma once

namespace dae
{
    // Type aliases
    using sound_id = unsigned short;
    
    class i_sound_system 
    {
    public:
        virtual ~i_sound_system() = default;

        virtual void play_sound(sound_id const id, float const volume = 1.0f) const = 0;
    };
}
