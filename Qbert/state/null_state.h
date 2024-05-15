#pragma once

// Project includes
#include "state/i_state.h"

namespace qbert
{
    class null_state final : public i_state
    {
    public:
        void on_enter() override { } 
        void update() override   { }
        void on_exit() override  { }
    };
}
