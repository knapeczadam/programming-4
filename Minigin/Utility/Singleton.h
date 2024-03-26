#pragma once

namespace dae
{
    template <typename T>
    class singleton
    {
    public:
        static T& get_instance()
        {
            static T instance{};
            return instance;
        }

        virtual ~singleton() = default;
        
        singleton(const singleton& other)            = delete;
        singleton(singleton&& other)                 = delete;
        singleton& operator=(const singleton& other) = delete;
        singleton& operator=(singleton&& other)      = delete;

    protected:
        singleton() = default;
    };
}
