#pragma once

// Project includes
#include "i_input.h"

namespace dae
{
    class sdl_input final : public i_input
    {
    public:
        auto do_process_input(std::vector<game_input_command> commands) -> bool override;
    };
}
