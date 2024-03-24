#pragma once

// Project includes
#include <string>
#include <vector>

namespace dae
{
    // Forward declaration
    class Subject;
    
    class Observer
    {
    public:
        virtual ~Observer() = default;

        virtual void Notify(const std::string& event, Subject* subject) = 0;
    };

    class Subject
    {
    public:
        virtual ~Subject() = default;

        void AddObserver(Observer* observer);
        void RemoveObserver(Observer* observer);

    protected:
        void NotifyObservers(const std::string& event);

    private:
        std::vector<Observer*> m_Observers{};
    };
}
