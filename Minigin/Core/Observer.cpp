#include "Observer.h"

namespace dae
{
    void Subject::AddObserver(Observer* observer)
    {
        m_Observers.push_back(observer);
    }

    void Subject::RemoveObserver(Observer* observer)
    {
        std::erase(m_Observers, observer);
    }

    void Subject::NotifyObservers(const std::string& event)
    {
        for (Observer* observer : m_Observers)
        {
            observer->Notify(event, this);
        }
    }
}
