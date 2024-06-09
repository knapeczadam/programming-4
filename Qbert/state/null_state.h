#pragma once

// Project includes
#include "state/state.h"

namespace qbert
{
    class null_state final : public state
    {
    public:
        void on_enter() override { } 
        void update()   override { }
        void on_exit()  override { }
    };
}
