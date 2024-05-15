#pragma once

// Project includes
#include "game_state.h"

namespace qbert
{
    class loosing_state final : public game_state
    {
    public:
        explicit loosing_state(mngn::scene *scene_ptr);

        void on_exit() override;
    };
}
