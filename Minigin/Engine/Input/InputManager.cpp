#include "InputManager.h"

#define WIN32_LEAN_AND_MEAN

// Standard includes
#include <iostream>
#include <thread>

// SDL includes
#include <SDL.h>
#include <SDL_syswm.h>

// ImGui includes
#include <backends/imgui_impl_sdl2.h>

#pragma comment(lib, "xinput.lib")

namespace dae
{
    bool InputManager::ProcessInput()
    {
        //---------------------------------------------------------------------------------
        // XInput
        //---------------------------------------------------------------------------------
        XINPUT_STATE previousState{};
        XINPUT_STATE currentState{};
        int controllerIndex {};
        
        CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
        ZeroMemory(&currentState, sizeof(XINPUT_STATE));
        XInputGetState(controllerIndex, &currentState);

        const auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
        const auto buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
        const auto buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

        static auto isDownThisFrame = [&](int button) -> bool
        {
            return buttonsPressedThisFrame & button;
        };

        static auto isUpThisFrame = [&](int button) -> bool
        {
            return buttonsReleasedThisFrame & button;
        };

        static auto isPressed = [&](int button) -> bool
        {
            return currentState.Gamepad.wButtons & button;
        };
        
        if (m_Commands.contains(InputType::Controller))
        {
            auto range = m_Commands.equal_range(InputType::Controller);
            for (auto it = range.first; it != range.second; ++it)
            {
                const auto inputState = std::get<0>(it->second);
                if (inputState == InputState::Down)
                {
                    const auto input = std::get<1>(it->second);
                    if (isDownThisFrame(input))
                    {
                        std::get<2>(it->second)->Execute();
                    }
                }
                if (inputState == InputState::Up)
                {
                    const auto input = std::get<1>(it->second);
                    if (isUpThisFrame(input))
                    {
                        std::get<2>(it->second)->Execute();
                    }
                }
                if (inputState == InputState::Pressed)
                {
                    const auto input = std::get<1>(it->second);
                    if (isPressed(input))
                    {
                        std::get<2>(it->second)->Execute();
                    }
                }
            }
        }

        //---------------------------------------------------------------------------------
        // SDL
        //---------------------------------------------------------------------------------
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT)
            {
                return false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (m_Commands.contains(InputType::Keyboard))
                {
                    auto range = m_Commands.equal_range(InputType::Keyboard);
                    for (auto it = range.first; it != range.second; ++it)
                    {
                        const auto inputState = std::get<0>(it->second);
                        if (inputState == InputState::Down)
                        {
                            const auto input = std::get<1>(it->second);
                            if (input == e.key.keysym.sym)
                            {
                                std::get<2>(it->second)->Execute();
                            }
                        }
                    }
                }
                if (e.type == SDL_KEYUP)
                {
                    if (m_Commands.contains(InputType::Keyboard))
                    {
                        auto range = m_Commands.equal_range(InputType::Keyboard);
                        for (auto it = range.first; it != range.second; ++it)
                        {
                            const auto inputState = std::get<0>(it->second);
                            if (inputState == InputState::Up)
                            {
                                const auto input = std::get<1>(it->second);
                                if (input == e.key.keysym.sym)
                                {
                                    std::get<2>(it->second)->Execute();
                                }
                            }
                        }
                    }
                }
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                }
            }
        }
        return true;
    }

    void InputManager::BindCommand(InputType inputType, InputState inputState, int input, std::unique_ptr<GameObjectCommand> command)
    {
        m_Commands.emplace(inputType, std::make_tuple(inputState, input, std::move(command)));
    }
}
