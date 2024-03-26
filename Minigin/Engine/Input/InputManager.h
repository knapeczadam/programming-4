#pragma once

// Project includes
#include "Singleton.h"

// Standard includes
#include <memory>
#include <vector>

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

        K_r = SDLK_r,
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
    class GameActorCommand;
    
    struct GameInputCommand
    {
        InputType inputType;
        InputState inputState;
        int input;
        GameActorCommand* command = nullptr;
    };
    
    class InputManager final : public Singleton<InputManager>
    {
    public:
        ~InputManager() override;
        
        bool ProcessInput();
        void BindCommand(InputType inputType, InputState inputState, int input, std::unique_ptr<GameActorCommand> command);
        bool UnbindCommand(InputType inputType, InputState inputState, int input);
        
    private:
        friend class Singleton<InputManager>;
        InputManager();

        class InputManagerImpl;
        std::unique_ptr<InputManagerImpl> m_implPtr;
    };
}
