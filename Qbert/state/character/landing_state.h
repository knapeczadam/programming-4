#pragma once

// Project includes
#include "character_state.h"

namespace qbert
{
    class landing_state final : public character_state
    {
    public:
        explicit landing_state(mngn::game_object* character_ptr);

        void on_enter() override;
    };
}
