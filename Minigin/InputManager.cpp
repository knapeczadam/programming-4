#include "InputManager.h"

// SDL includes
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
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
