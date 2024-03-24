#pragma once

// Project includes
#include "GameObjectCommand.h"
#include "Singleton.h"

// Standard includes
#include <memory>
#include <unordered_map>

// SDL includes
#include <SDL.h>

// Windows includes
#include <windows.h>
#include <XInput.h>

namespace dae
{
    enum class InputType
    {
        Keyboard,
        Mouse,
        Controller
    };
    enum class InputState
    {
        Down,
        Up,
        Pressed
    };

    enum Input
    {
        K_LEFT = SDLK_LEFT,
        K_RIGHT = SDLK_RIGHT,
        K_UP = SDLK_UP,
        K_DOWN = SDLK_DOWN,

        K_a = SDLK_a,
        K_d = SDLK_d,
        K_w = SDLK_w,
        K_s = SDLK_s,

        K_c = SDLK_c,
        K_z = SDLK_z,
        K_x = SDLK_x,

        C_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
        C_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
        C_UP = XINPUT_GAMEPAD_DPAD_UP,
        C_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,

        C_A = XINPUT_GAMEPAD_A,
        C_B = XINPUT_GAMEPAD_B,
        C_X = XINPUT_GAMEPAD_X,
        C_Y = XINPUT_GAMEPAD_Y
    };
    
    // Forward declarations
    class GameObjectCommand;
    
    class InputManager final : public Singleton<InputManager>
    {
    public:
        bool ProcessInput();
        void BindCommand(InputType inputType, InputState inputState, int input, std::unique_ptr<GameObjectCommand> command);
        bool UnbindCommand(InputType inputType, InputState inputState, int input);
        
    private:
        friend class Singleton<InputManager>;
        InputManager() = default;
        
        std::unordered_multimap<InputType, std::tuple<InputState, int, std::unique_ptr<GameObjectCommand>>> m_Commands;
    };
}
