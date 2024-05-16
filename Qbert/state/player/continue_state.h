#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class continue_state final : public character_state
    {
    public:
        explicit continue_state(mngn::game_object* character_ptr);

        void on_enter() override;
    };
}
