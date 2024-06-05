#include "sound_system.h"

namespace mngn
{
    sound_system::sound_system()
    {
        thread_ = std::jthread([this]
        {
            run();
        });
    }

    sound_system::~sound_system()
    {
        running_ = false;
        event_condition_.notify_all();
    }

    void sound_system::add_event(sound_event event)
    {
        std::lock_guard<std::mutex> lock{mutex_};
        event_queue_.push(event);
        event_condition_.notify_one();
    }

    void sound_system::play_sound(int id, int volume)
    {
        add_event({id, volume});
    }

    void sound_system::run()
    {
        while (running_)
        {
            std::unique_lock<std::mutex> lock{mutex_};
            event_condition_.wait(lock, [this]
            {
                return not event_queue_.empty() or not running_;
            });
            while (not event_queue_.empty())
            {
                auto event = event_queue_.front();
                event_queue_.pop();
                play_sound_impl(event.sound_id, event.volume);
            }
        }
    }
}
