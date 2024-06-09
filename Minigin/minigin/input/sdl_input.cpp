#include "sdl_input.h"

// Project includes
#include "minigin/input/game_object_command.h"
#include "minigin/input/input_manager.h"

// Standard includes
#include <algorithm>
#include <ranges>

// SDL includes
#include <SDL.h>

// ImGui includes
#include <backends/imgui_impl_sdl2.h>

namespace mngn
{
    auto sdl_input::do_process_input(std::vector<input_config_info> input_configs) -> bool
    {
        auto key_commands = input_configs | std::views::filter([](auto const &input_config) { return input_config.input_type == input_type::keyboard; });
        
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
                auto key_down_commands = key_commands | std::views::filter([](auto const &command)
                {
                    return command.input_state == input_state::down;
                });
                for (auto const &game_command : key_down_commands)
                {
                    if (remap(game_command.input) == e.key.keysym.sym and e.key.repeat == 0)
                    {
                        game_command.command_ptr->execute();
                    }
                }
            }
            if (e.type == SDL_KEYUP)
            {
                auto key_up_commands = key_commands | std::views::filter([](auto const &command)
                {
                    return command.input_state == input_state::up;
                });
                for (auto const &game_command : key_up_commands)
                {
                    if (remap(game_command.input) == e.key.keysym.sym and e.key.repeat == 0)
                    {
                        game_command.command_ptr->execute();
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
            }
        }
        return true;
    }

    int sdl_input::remap(input input)
    {
        switch (input)
        {
        case input::k_1:
            return SDLK_1;
        case input::k_2:
            return SDLK_2;
        case input::k_3:
            return SDLK_3;
        case input::k_left:
            return SDLK_LEFT;
        case input::k_right:
            return SDLK_RIGHT;
        case input::k_up:
            return SDLK_UP;
        case input::k_down:
            return SDLK_DOWN;
        case input::k_return:
            return SDLK_RETURN;
        case input::k_right_shift:
            return SDLK_RSHIFT;
        case input::k_a:
            return SDLK_a;
        case input::k_d:
            return SDLK_d;
        case input::k_w:
            return SDLK_w;
        case input::k_s:
            return SDLK_s;
        case input::k_r:
            return SDLK_r;
        case input::k_c:
            return SDLK_c;
        case input::k_z:
            return SDLK_z;
        case input::k_x:
            return SDLK_x;
        case input::k_j:
            return SDLK_j;
        case input::k_m:
            return SDLK_m;
        case input::k_f1:
            return SDLK_F1;
        default:
            return 0;
        }
    }
}
