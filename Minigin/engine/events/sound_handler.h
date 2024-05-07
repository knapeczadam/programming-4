﻿#pragma once

// Project includes
#include "event_handler.h"

namespace dae
{
    class sound_handler final : public event_handler
    {
    protected:
        void run_impl(event *event_ptr) override;
    };
}
