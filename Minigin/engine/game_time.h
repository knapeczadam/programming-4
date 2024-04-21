#pragma once

// Project includes
#include "utility/singleton.h"

namespace dae
{
    class game_time final : public singleton<game_time>
    {
    public:
        float delta_time = 0.0f;
        
        float const fixed_time_step = 0.02f;
        float const ms_per_frame = 0.0f;
        
    private:
        friend class singleton<game_time>;
        game_time() = default;
    };
}
