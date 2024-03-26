#include "IObserver.h"

namespace dae
{
    void Subject::AddObserver(IObserver* observer)
    {
        m_Observers.push_back(observer);
    }

    void Subject::RemoveObserver(IObserver* observer)
    {
        std::erase(m_Observers, observer);
    }

    void Subject::NotifyObservers(const std::string& event)
    {
        for (IObserver* observer : m_Observers)
        {
            observer->Notify(event, this);
        }
    }
}
