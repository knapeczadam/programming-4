#pragma once

// Project includes
#include "i_input.h"

namespace mngn
{
    class sdl_input final : public i_input
    {
    public:
        auto do_process_input(std::vector<input_config_info> commands) -> bool override;
    };
}
