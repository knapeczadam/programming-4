#pragma once

namespace dae
{
    // Forward declarations
    enum class resource_id;
    
    class i_sound_system 
    {
    public:
        virtual ~i_sound_system() = default;

        virtual void play_sound(resource_id id, int const volume = 1) = 0;
    };
}
