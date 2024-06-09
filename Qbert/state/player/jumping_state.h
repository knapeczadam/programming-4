#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class jumping_state final : public character_state
    {
    public:
        explicit jumping_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void on_exit()  override;
    };
}
