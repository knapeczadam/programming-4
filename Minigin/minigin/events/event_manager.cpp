﻿#include "event_manager.h"

// Project includes
#include "event_handler.h"

// Standard includes
#include <ranges>

namespace mngn
{
    event_manager::event_manager() = default;

    event_manager::~event_manager() = default;
    
    void event_manager::stop_all()
    {
        for (auto const &event : event_handlers_ | std::views::values)
        {
            event->stop_thread();
        }
    }
}
