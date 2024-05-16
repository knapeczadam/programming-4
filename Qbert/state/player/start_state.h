#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class start_state final : public character_state
    {
    public:
        explicit start_state(mngn::game_object* character_ptr);

        void on_enter() override;
    };
}
