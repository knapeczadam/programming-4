#include "XInputImpl.h"

#define WIN32_LEAN_AND_MEAN

// Project includes
#include "GameActorCommand.h"
#include "InputManager.h"

// Standard includes
#include <algorithm>
#include <ranges>
#include <thread>

#pragma comment(lib, "xinput.lib")

namespace dae
{
    auto x_input_impl::do_process_input(std::vector<game_input_command> commands) -> bool
    {
        CopyMemory(&previous_state_, &current_state_, sizeof(XINPUT_STATE));
        ZeroMemory(&current_state_, sizeof(XINPUT_STATE));
        XInputGetState(controller_index_, &current_state_);

        const auto buttonChanges = current_state_.Gamepad.wButtons ^ previous_state_.Gamepad.wButtons;
        buttons_pressed_this_frame_ = buttonChanges & current_state_.Gamepad.wButtons;
        buttons_released_this_frame_ = buttonChanges & (~current_state_.Gamepad.wButtons);

        auto controller_commands = commands | std::views::filter([](const game_input_command& command) { return command.input_type == input_type::controller; });
        for (const auto& game_command : controller_commands)
        {
            const auto input_state = game_command.input_state;
            if (input_state == input_state::down)
            {
                const auto input = game_command.input;
                if (is_down_this_frame(input))
                {
                    game_command.command->execute();
                }
            }
            if (input_state == input_state::up)
            {
                const auto input = game_command.input;
                if (is_up_this_frame(input))
                {
                    game_command.command->execute();
                }
            }
            if (input_state == input_state::pressed)
            {
                const auto input = game_command.input;
                if (is_pressed(input))
                {
                    game_command.command->execute();
                }
            }
        }
        return true;
    }

    auto x_input_impl::is_down_this_frame(int button) const -> bool
    {
        return buttons_pressed_this_frame_ & button;
    }

    auto x_input_impl::is_up_this_frame(int button) const -> bool
    {
        return buttons_released_this_frame_ & button;
    }

    auto x_input_impl::is_pressed(int button) const -> bool
    {
        return current_state_.Gamepad.wButtons & button;
    }
}
