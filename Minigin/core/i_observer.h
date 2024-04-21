#pragma once

// Project includes
#include <string>
#include <vector>

namespace dae
{
    // Forward declaration
    class subject;
    
    class i_observer
    {
    public:
        i_observer()          = default;
        virtual ~i_observer() = default;

        i_observer(i_observer const &other)            = delete;
        i_observer(i_observer &&other)                 = delete;
        i_observer &operator=(i_observer const &other) = delete;
        i_observer &operator=(i_observer &&other)      = delete;

        virtual void notify(std::string const &event, subject *subject_ptr) = 0;
    };

    class subject 
    {
    public:
        subject()          = default;
        virtual ~subject() = default;

        subject(subject const &other)            = delete;
        subject(subject &&other)                 = delete;
        subject &operator=(subject const &other) = delete;
        subject &operator=(subject &&other)      = delete;

        void add_observer(i_observer *observer_ptr);
        void remove_observer(i_observer *observer_ptr);

    protected:
        void notify_observers(std::string const &event);

    private:
        std::vector<i_observer*> observers_{};
    };
}
