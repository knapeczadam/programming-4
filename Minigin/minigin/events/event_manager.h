#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace mngn
{
    // Forward declarations
    class event_handler;

    // Concepts
    template <class T>
    concept is_event_handler = std::is_base_of_v<event_handler, T> and std::is_constructible_v<T>;
    
    class event_manager final : public singleton<event_manager>
    {
    public:
        ~event_manager() override;

        event_manager(event_manager const &other) = delete;
        event_manager(event_manager &&other) = delete;
        event_manager &operator=(event_manager const &other) = delete;
        event_manager &operator=(event_manager &&other) = delete;

        template <class T> requires is_event_handler<T>
        auto get_handler() -> T *;

        void stop_all();

    private:
        friend class singleton<event_manager>;
        event_manager();

        std::unordered_map<std::type_index, std::unique_ptr<event_handler>> event_handlers_ = {};
    };
}

#include "event_manager.hpp"
