#pragma once

// Project includes
#include "state/i_state.h"

namespace qbert
{
    class ui_state : public i_state
    {
    public:
        void on_enter() override { }
        void update()   override { }
        void on_exit()  override { }
    };
}
