#include "event_handler.h"

// Project includes
#include "event.h"

namespace dae
{
    event_handler::event_handler()
    {
        thread_ = std::jthread([this](std::stop_token st) { run(st); });
    }

    void event_handler::add_event(std::unique_ptr<event> event)
    {
        std::lock_guard<std::mutex> lock{mutex_};
        event_queue_.push(std::move(event));
        event_condition_.notify_one();
    }

    void event_handler::stop_thread()
    {
        thread_.request_stop();
    }

    void event_handler::run(std::stop_token st)
    {
        while (not st.stop_requested())
        {
            std::unique_lock<std::mutex> lock{mutex_};
            event_condition_.wait(lock, [this] { return not event_queue_.empty(); });
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
