#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class playing_state final : public game_state
    {
    public:
        explicit playing_state(mngn::scene *scene_ptr);

        void on_exit() override;
    };
}
