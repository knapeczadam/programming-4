#pragma once

// Project includes
#include "event_handler.h"

namespace mngn
{
    class sound_handler final : public event_handler
    {
    protected:
        void run_impl(event *event_ptr) override;
    };
}
