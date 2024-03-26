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
    auto XInputImpl::DoProcessInput(std::vector<GameInputCommand> commands) -> bool
    {
        CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
        XInputGetState(controllerIndex, &m_currentState);

        const auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
        buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
        buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);

        auto controllerCommands = commands | std::views::filter([](const GameInputCommand& command) { return command.inputType == InputType::Controller; });
        for (const auto& gameCommand : controllerCommands)
        {
            const auto inputState = gameCommand.inputState;
            if (inputState == InputState::Down)
            {
                const auto input = gameCommand.input;
                if (IsDownThisFrame(input))
                {
                    gameCommand.command->Execute();
                }
            }
            if (inputState == InputState::Up)
            {
                const auto input = gameCommand.input;
                if (IsUpThisFrame(input))
                {
                    gameCommand.command->Execute();
                }
            }
            if (inputState == InputState::Pressed)
            {
                const auto input = gameCommand.input;
                if (IsPressed(input))
                {
                    gameCommand.command->Execute();
                }
            }
        }
        return true;
    }

    auto XInputImpl::IsDownThisFrame(int button) const -> bool
    {
        return buttonsPressedThisFrame & button;
    }

    auto XInputImpl::IsUpThisFrame(int button) const -> bool
    {
        return buttonsReleasedThisFrame & button;
    }

    auto XInputImpl::IsPressed(int button) const -> bool
    {
        return m_currentState.Gamepad.wButtons & button;
    }
}
