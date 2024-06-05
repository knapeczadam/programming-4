#pragma once

// Project includes
#include "minigin/input/i_input.h"

namespace mngn
{
    class sdl_input final : public i_input
    {
    public:
        auto do_process_input(std::vector<input_config_info> input_configs) -> bool override;

    protected:
        int remap(input input) override;
    };
}
