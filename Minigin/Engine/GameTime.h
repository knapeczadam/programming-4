#pragma once

// Project includes
#include "Singleton.h"

namespace dae
{
    class game_time final : public singleton<game_time>
    {
    public:
        float delta_time_ = 0.0f;
        
        const float fixed_time_step_ = 0.02f;
        const float ms_per_frame_ = 16.666666666666668f;
    private:
        friend class singleton<game_time>;
        game_time() = default;
    };
}
