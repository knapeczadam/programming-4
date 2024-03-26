#include "i_observer.h"

namespace dae
{
    void subject::add_observer(i_observer* observer)
    {
        observers_.push_back(observer);
    }

    void subject::remove_observer(i_observer* observer)
    {
        std::erase(observers_, observer);
    }

    void subject::notify_observers(const std::string& event)
    {
        for (i_observer* observer : observers_)
        {
            observer->notify(event, this);
        }
    }
}
