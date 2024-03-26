#pragma once

// Project includes
#include <string>
#include <vector>

namespace dae
{
    // Forward declaration
    class Subject;
    
    class IObserver
    {
    public:
        virtual ~IObserver() = default;

        virtual void Notify(const std::string& event, Subject* subject) = 0;
    };

    class Subject 
    {
    public:
        virtual ~Subject() = default;

        void AddObserver(IObserver* observer);
        void RemoveObserver(IObserver* observer);

    protected:
        void NotifyObservers(const std::string& event);

    private:
        std::vector<IObserver*> m_Observers{};
    };
}
