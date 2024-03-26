#include "sdl_input.h"

// Project includes
#include "game_object_command.h"
#include "input_manager.h"

// Standard includes
#include <algorithm>
#include <ranges>

// SDL includes
#include <SDL.h>

// ImGui includes
#include <backends/imgui_impl_sdl2.h>

namespace dae
{
    auto sdl_input::do_process_input(std::vector<game_input_command> commands) -> bool
    {
        auto key_commands = commands | std::views::filter([](const auto& command) { return command.input_type == input_type::keyboard; });
        
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
                auto key_down_commands = key_commands | std::views::filter([](const auto& command) { return command.input_state == input_state::down; });
                for (const auto& game_command : key_down_commands)
                {
                    if (game_command.input == e.key.keysym.sym)
                    {
                        game_command.command->execute();
                    }
                }
                if (e.type == SDL_KEYUP)
                {
                    auto key_up_commands = key_commands | std::views::filter([](const auto& command) { return command.input_state == input_state::up; });
                    for (const auto& game_command : key_up_commands)
                    {
                        if (game_command.input == e.key.keysym.sym)
                        {
                            game_command.command->execute();
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
}
