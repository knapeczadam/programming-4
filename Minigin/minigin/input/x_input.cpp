#include "x_input.h"

// Project includes
#include "minigin/input/game_object_command.h"
#include "minigin/input/input_manager.h"

// Standard includes
#include <algorithm>
#include <ranges>
#include <thread>

// Windows includes
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "xinput.lib")

namespace mngn
{
    auto x_input::do_process_input(std::vector<input_config_info> input_configs) -> bool
    {
        CopyMemory(&previous_state_, &current_state_, sizeof(XINPUT_STATE));
        ZeroMemory(&current_state_, sizeof(XINPUT_STATE));
        XInputGetState(controller_index_, &current_state_);

        auto const button_changes = current_state_.Gamepad.wButtons ^ previous_state_.Gamepad.wButtons;
        buttons_pressed_this_frame_ = button_changes & current_state_.Gamepad.wButtons;
        buttons_released_this_frame_ = button_changes & (~current_state_.Gamepad.wButtons);

        auto controller_commands = input_configs | std::views::filter([](input_config_info const &input_config) { return input_config.input_type == input_type::controller; });
        for (auto const &game_command : controller_commands)
        {
            if (game_command.controller_idx == controller_index_)
            {
                auto const input_state = game_command.input_state;
                
                if (input_state == input_state::down)
                {
                    auto const input = game_command.input;
                    if (is_down_this_frame(remap(input)))
                    {
                        game_command.command_ptr->execute();
                    }
                }
                if (input_state == input_state::up)
                {
                    auto const input = game_command.input;
                    if (is_up_this_frame(remap(input)))
                    {
                        game_command.command_ptr->execute();
                    }
                }
                if (input_state == input_state::pressed)
                {
                    auto const input = game_command.input;
                    if (is_pressed(remap(input)))
                    {
                        game_command.command_ptr->execute();
                    }
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

    int x_input::remap(input input)
    {
        switch (input)
        {
        case input::c_left:
            return XINPUT_GAMEPAD_DPAD_LEFT;
        case input::c_right:
            return XINPUT_GAMEPAD_DPAD_RIGHT;
        case input::c_up:
            return XINPUT_GAMEPAD_DPAD_UP;
        case input::c_down:
            return XINPUT_GAMEPAD_DPAD_DOWN;
        case input::c_a:
            return XINPUT_GAMEPAD_A;
        case input::c_b:
            return XINPUT_GAMEPAD_B;
        case input::c_x:
            return XINPUT_GAMEPAD_X;
        case input::c_y:
            return XINPUT_GAMEPAD_Y;
        default:
                return 0;
        }
    }
}
