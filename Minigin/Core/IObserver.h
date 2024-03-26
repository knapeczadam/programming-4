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
        i_observer() = default;
        virtual ~i_observer() = default;

        i_observer(const i_observer& other)            = delete;
        i_observer(i_observer&& other)                 = delete;
        i_observer& operator=(const i_observer& other) = delete;
        i_observer& operator=(i_observer&& other)      = delete;

        virtual void notify(const std::string& event, subject* subject) = 0;
    };

    class subject 
    {
    public:
        subject() = default;
        virtual ~subject() = default;

        subject(const subject& other)            = delete;
        subject(subject&& other)                 = delete;
        subject& operator=(const subject& other) = delete;
        subject& operator=(subject&& other)      = delete;

        void add_observer(i_observer* observer);
        void remove_observer(i_observer* observer);

    protected:
        void notify_observers(const std::string& event);

    private:
        std::vector<i_observer*> observers_{};
    };
}
