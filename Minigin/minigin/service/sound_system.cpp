#include "sound_system.h"

// Standard includes
#include <condition_variable>
#include <mutex>
#include <queue>

namespace mngn
{
    class sound_system::sound_system_impl
    {
    public:
        explicit sound_system_impl(sound_system *parent_ptr)
            : parent_ptr_{parent_ptr}
        {
            thread_ = std::jthread([this]
            {
                run();
            });
        }

        ~sound_system_impl()
        {
            running_ = false;
            event_condition_.notify_all();
        }

        sound_system_impl(sound_system_impl const &other)            = delete;
        sound_system_impl(sound_system_impl &&other)                 = delete;
        sound_system_impl &operator=(sound_system_impl const &other) = delete;
        sound_system_impl &operator=(sound_system_impl &&other)      = delete;

        void add_event(sound_event event)
        {
            std::lock_guard<std::mutex> lock{mutex_};
            event_queue_.push(event);
            event_condition_.notify_one();
        }

    private:
        void run()
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
                    parent_ptr_->play_sound_impl(event.sound_id, event.volume);
                }
            }
        }
        
    private:
        std::jthread thread_;
        std::queue<sound_event> event_queue_;
        std::mutex mutex_;
        std::condition_variable event_condition_;

        bool running_ = true;
        sound_system *parent_ptr_;
    };
    
    sound_system::sound_system()
    {
        impl_ = std::make_unique<sound_system_impl>(this);
    }

    sound_system::~sound_system() = default;

    void sound_system::play_sound(int id, int volume)
    {
        impl_->add_event({id, volume});
    }
}
