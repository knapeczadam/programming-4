#pragma once

// Project includes
#include "minigin/utility/singleton.h"

namespace mngn
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
