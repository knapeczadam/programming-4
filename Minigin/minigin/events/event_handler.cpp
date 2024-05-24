#include "event_handler.h"

// Project includes
#include "event.h"

namespace mngn
{
    event_handler::event_handler()
    {
        thread_ = std::jthread([this]() { run(); });
    }

    void event_handler::add_event(std::unique_ptr<event> event)
    {
        std::lock_guard<std::mutex> lock{mutex_};
        event_queue_.push(std::move(event));
        event_condition_.notify_one();
    }

    void event_handler::stop_thread()
    {
        running_ = false;
        event_condition_.notify_one();
    }

    void event_handler::run()
    {
        while (running_)
        {
            std::unique_lock<std::mutex> lock{mutex_};
            event_condition_.wait(lock, [this] { return not event_queue_.empty() or not running_; });
            while (not event_queue_.empty())
            {
                auto event = std::move(event_queue_.front());
                event_queue_.pop();
                lock.unlock(); // TODO
                run_impl(event.get());
            }
        }
    }
}
