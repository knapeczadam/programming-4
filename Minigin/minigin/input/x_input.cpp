#include "x_input.h"

#define WIN32_LEAN_AND_MEAN

// Project includes
#include "game_object_command.h"
#include "input_manager.h"

// Standard includes
#include <algorithm>
#include <ranges>
#include <thread>

#pragma comment(lib, "xinput.lib")

namespace mngn
{
    auto x_input::do_process_input(std::vector<game_input_command> commands) -> bool
    {
        CopyMemory(&previous_state_, &current_state_, sizeof(XINPUT_STATE));
        ZeroMemory(&current_state_, sizeof(XINPUT_STATE));
        XInputGetState(controller_index_, &current_state_);

        auto const button_changes = current_state_.Gamepad.wButtons ^ previous_state_.Gamepad.wButtons;
        buttons_pressed_this_frame_ = button_changes & current_state_.Gamepad.wButtons;
        buttons_released_this_frame_ = button_changes & (~current_state_.Gamepad.wButtons);

        auto controller_commands = commands | std::views::filter([](game_input_command const &command) { return command.input_type == input_type::controller; });
        for (auto const &game_command : controller_commands)
        {
            auto const input_state = game_command.input_state;
            if (input_state == input_state::down)
            {
                auto const input = game_command.input;
                if (is_down_this_frame(input))
                {
                    game_command.command_ptr->execute();
                }
            }
            if (input_state == input_state::up)
            {
                auto const input = game_command.input;
                if (is_up_this_frame(input))
                {
                    game_command.command_ptr->execute();
                }
            }
            if (input_state == input_state::pressed)
            {
                auto const input = game_command.input;
                if (is_pressed(input))
                {
                    game_command.command_ptr->execute();
                }
            }
        }
        return true;
    }

    auto x_input::is_down_this_frame(int button) const -> bool
    {
        return buttons_pressed_this_frame_ & button;
    }

    auto x_input::is_up_this_frame(int button) const -> bool
    {
        return buttons_released_this_frame_ & button;
    }

    auto x_input::is_pressed(int button) const -> bool
    {
        return current_state_.Gamepad.wButtons & button;
    }
}
