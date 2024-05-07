#pragma once

namespace mngn
{
    // Forward declaration
    class event_manager;
    
    template <class T> requires is_event_handler<T>
    auto event_manager::get_handler() -> T *
    {
        if (event_handlers_.contains(typeid(T)))
        {
            return static_cast<T*>(event_handlers_.at(typeid(T)).get());
        }
        auto handler = std::make_unique<T>();
        auto copy_ptr = handler.get();
        event_handlers_[typeid(T)] = std::move(handler);
        return copy_ptr;
    }
}
