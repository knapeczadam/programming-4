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
    enum class input_type
    {
        keyboard,
        mouse,
        controller
    };
    enum class input_state
    {
        down,
        up,
        pressed
    };

    enum input
    {
        k_left = SDLK_LEFT,
        k_right = SDLK_RIGHT,
        k_up = SDLK_UP,
        k_down = SDLK_DOWN,

        k_a = SDLK_a,
        k_d = SDLK_d,
        k_w = SDLK_w,
        k_s = SDLK_s,

        k_r = SDLK_r,
        k_c = SDLK_c,
        k_z = SDLK_z,
        k_x = SDLK_x,

        c_left = XINPUT_GAMEPAD_DPAD_LEFT,
        c_right = XINPUT_GAMEPAD_DPAD_RIGHT,
        c_up = XINPUT_GAMEPAD_DPAD_UP,
        c_down = XINPUT_GAMEPAD_DPAD_DOWN,

        c_a = XINPUT_GAMEPAD_A,
        c_b = XINPUT_GAMEPAD_B,
        c_x = XINPUT_GAMEPAD_X,
        c_y = XINPUT_GAMEPAD_Y
    };
    
    // Forward declarations
    class game_command;
    class game_object_command;
    
    struct game_input_command
    {
        input_type input_type;
        input_state input_state;
        int input;
        game_command* command = nullptr;
    };
    
    class input_manager final : public singleton<input_manager>
    {
    public:
        ~input_manager() override;

        input_manager(const input_manager& other)            = delete;
        input_manager(input_manager&& other)                 = delete;
        input_manager& operator=(const input_manager& other) = delete;
        input_manager& operator=(input_manager&& other)      = delete;

        [[nodiscard]] auto process_input() const -> bool;
        
        void bind_command(input_type input_type, input_state input_state, int input, std::unique_ptr<game_command> command) const;
        [[nodiscard]] auto unbind_command(input_type input_type, input_state input_state, int input) const -> bool;
        
    private:
        friend class singleton<input_manager>;
        input_manager();

        class input_manager_impl;
        std::unique_ptr<input_manager_impl> impl_ptr_;
    };
}
