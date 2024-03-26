#pragma once

// GLM includes
#include <glm/vec2.hpp>

// Forward declarations
struct SDL_Texture;

namespace dae
{
    /**
     * Simple RAII wrapper for an SDL_Texture
     */
    class texture_2d final
    {
    public:
        explicit texture_2d(SDL_Texture* texture);
        ~texture_2d();
        
        texture_2d(const texture_2d&)             = delete;
        texture_2d(texture_2d&&)                  = delete;
        texture_2d& operator=(const texture_2d&)  = delete;
        texture_2d& operator=(const texture_2d&&) = delete;

        auto get_sdl_texture() const -> SDL_Texture*;
        auto get_size() const -> glm::ivec2;

    private:
        SDL_Texture* texture_;
    };
}
