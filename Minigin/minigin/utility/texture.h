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
    class texture final
    {
    public:
        explicit texture(SDL_Texture *texture_ptr);
        ~texture();
        
        texture(texture const &other)             = delete;
        texture(texture &&other)                  = delete;
        texture &operator=(texture const &other)  = delete;
        texture &operator=(texture &&other)       = delete;

        [[nodiscard]] auto sdl_texture() const -> SDL_Texture * { return texture_ptr_; }
        [[nodiscard]] auto size() const -> glm::ivec2;
        [[nodiscard]] auto width() const -> int { return size().x; }
        [[nodiscard]] auto height() const -> int { return size().y; }

    private:
        SDL_Texture *texture_ptr_;
    };
}
