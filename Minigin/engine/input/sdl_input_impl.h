#pragma once

// Project includes
#include "i_input_impl.h"

namespace dae
{
    class sdl_input_impl : public i_input_impl
    {
    public:
        auto do_process_input(std::vector<game_input_command> commands) -> bool override;
    };
}
