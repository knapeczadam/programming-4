#include "SDLInputImpl.h"

// Project includes
#include "GameActorCommand.h"
#include "InputManager.h"

// Standard includes
#include <algorithm>
#include <ranges>

// SDL includes
#include <SDL.h>

// ImGui includes
#include <backends/imgui_impl_sdl2.h>

namespace dae
{
    auto SDLInputImpl::DoProcessInput(std::vector<GameInputCommand> commands) -> bool
    {
        auto keyCommands = commands | std::views::filter([](const auto& command) { return command.inputType == InputType::Keyboard; });
        
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
                auto keyDownCommands = keyCommands | std::views::filter([](const auto& command) { return command.inputState == InputState::Down; });
                for (const auto& gameCommand : keyDownCommands)
                {
                    if (gameCommand.input == e.key.keysym.sym)
                    {
                        gameCommand.command->Execute();
                    }
                }
                if (e.type == SDL_KEYUP)
                {
                    auto keyUpCommands = keyCommands | std::views::filter([](const auto& command) { return command.inputState == InputState::Up; });
                    for (const auto& gameCommand : keyUpCommands)
                    {
                        if (gameCommand.input == e.key.keysym.sym)
                        {
                            gameCommand.command->Execute();
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
