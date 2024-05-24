#pragma once

// Project includes
#include "i_input.h"

// Windows includes
#include <windows.h>
#include <XInput.h>

namespace mngn
{
    class x_input final : public i_input
    {
    public:
        auto do_process_input(std::vector<input_config_info> commands) -> bool override;

    private:
        [[nodiscard]] auto is_down_this_frame(int button) const -> bool;
        [[nodiscard]] auto is_up_this_frame(int button) const -> bool;
        [[nodiscard]] auto is_pressed(int button) const -> bool;

    private:
        XINPUT_STATE previous_state_              = {};
        XINPUT_STATE current_state_               = {};
        int          controller_index_            = 0;
        int          buttons_pressed_this_frame_  = 0;
        int          buttons_released_this_frame_ = 0;
    };
}
