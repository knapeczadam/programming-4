#pragma once

// Project includes
#include "state/player_state.h"

namespace qbert
{
    // Forward declarations
    class disc_component;
    
    class flying_state final : public player_state
    {
    public:
        explicit flying_state(mngn::game_object* player_ptr, disc_component* disc_ptr);

        void on_enter() override;
        void on_exit() override;

    private:
        disc_component *disc_ptr_ = nullptr;
    };
}
