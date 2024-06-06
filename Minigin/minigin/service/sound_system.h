#pragma once

// Standard includes
#include <memory>

namespace mngn
{
    class sound_system
    {
        struct sound_event
        {
            int sound_id;
            int volume;
        };
        
    public:
        sound_system();
        virtual ~sound_system();

        sound_system(sound_system const &other)            = delete;
        sound_system(sound_system &&other)                 = delete;
        sound_system &operator=(sound_system const &other) = delete;
        sound_system &operator=(sound_system &&other)      = delete;

        void play_sound(int id, int volume);

    protected:
        virtual void play_sound_impl(int id, int volume) = 0;

    private:
        class sound_system_impl;
        std::unique_ptr<sound_system_impl> impl_;
    };
}
