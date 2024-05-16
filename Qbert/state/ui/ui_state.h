#pragma once

// Project includes
#include "state/state.h"

namespace qbert
{
    class ui_state : public state
    {
    public:
        void on_enter() override { }
        void update()   override { }
        void on_exit()  override { }
    };
}
