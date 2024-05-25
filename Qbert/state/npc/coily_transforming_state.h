#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class coily_transforming_state final : public character_state
    {
    public:
        explicit coily_transforming_state(mngn::game_object* character_ptr);

        void update() override;

    private:
        float transform_time_ = 2.0f;
        float accu_time_      = 0.0f;
    };
}
