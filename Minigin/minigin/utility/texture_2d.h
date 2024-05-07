#pragma once

// GLM includes
#include <glm/vec2.hpp>

// Forward declarations
struct SDL_Texture;

namespace mngn
{
    /**
     * Simple RAII wrapper for an SDL_Texture
     */
    class texture_2d final
    {
    public:
        explicit texture_2d(SDL_Texture *texture_ptr);
        ~texture_2d();
        
        texture_2d(texture_2d const &other)             = delete;
        texture_2d(texture_2d &&other)                  = delete;
        texture_2d &operator=(texture_2d const &other)  = delete;
        texture_2d &operator=(texture_2d &&other)       = delete;

        [[nodiscard]] auto get_sdl_texture() const -> SDL_Texture *;
        [[nodiscard]] auto get_size() const -> glm::ivec2;

    private:
        SDL_Texture *texture_ptr_;
    };
}
