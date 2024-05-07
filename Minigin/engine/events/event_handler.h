#pragma once

// Standard includes
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <functional>

namespace dae
{
    // Forward declarations
    class event;
    
    class event_handler
    {
    public:
        event_handler();
        virtual ~event_handler() = default;

        event_handler(event_handler const &other)            = delete;
        event_handler(event_handler &&other)                 = delete;
        event_handler &operator=(event_handler const &other) = delete;
        event_handler &operator=(event_handler &&other)      = delete;

        void add_event(std::unique_ptr<event> event);
        void stop_thread();

    protected:
        virtual void run_impl(event *event_ptr) = 0;
        
    private:
        void run(std::stop_token st);
        
    protected:
        std::queue<std::unique_ptr<event>> event_queue_;
        std::mutex mutex_;
        std::jthread thread_;
        std::condition_variable event_condition_;
    };
}
