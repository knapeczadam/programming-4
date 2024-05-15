#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class game_over_state final : public game_state
    {
    public:
        explicit game_over_state(mngn::scene *scene_ptr);

        void on_exit() override;
    };
}
