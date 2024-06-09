#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class dead_state final : public character_state
    {
    public:
        explicit dead_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void on_exit()  override;
    };
}
