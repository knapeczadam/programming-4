#include "i_observer.h"

namespace mngn
{
    void subject::add_observer(i_observer *observer_ptr)
    {
        observers_.push_back(observer_ptr);
    }

    void subject::remove_observer(i_observer *observer_ptr)
    {
        std::erase(observers_, observer_ptr);
    }

    void subject::notify_observers(std::string const &event)
    {
        for (i_observer *observer_ptr : observers_)
        {
            observer_ptr->notify(event, this);
        }
    }
}
