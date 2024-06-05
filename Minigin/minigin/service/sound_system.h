#pragma once

// Standard includes
#include <condition_variable>
#include <mutex>
#include <queue>

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

        void play_sound(int id, int volume = 100);

    protected:
        virtual void play_sound_impl(int id, int volume) = 0;
        void run();
        
    private:
        void add_event(sound_event event);

    private:
        std::jthread thread_;
        std::queue<sound_event> event_queue_;
        std::mutex mutex_;
        std::condition_variable event_condition_;

        bool running_ = true;
    };
}
