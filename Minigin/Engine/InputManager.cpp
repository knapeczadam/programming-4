#include "InputManager.h"

// SDL includes
#include <SDL.h>

// ImGui includes
#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>

namespace dae
{
    bool InputManager::ProcessInput()
    {
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
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
            }
            // etc...
        }

        return true;
    }
}
