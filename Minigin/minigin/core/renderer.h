#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// SDL includes
#include <SDL.h>

namespace mngn
{
    class texture_2d;
    /**
     * Simple RAII wrapper for the SDL renderer
     */
    class renderer final : public singleton<renderer>
    {
    public:
        void init(SDL_Window *window_ptr);
        void render() const;
        void destroy();

        void render_texture(texture_2d const &texture, float x, float y) const;
        void render_texture(texture_2d const &texture, float x, float y, float width, float height) const;

        [[nodiscard]] auto get_sdl_renderer() const -> SDL_Renderer *;

        [[nodiscard]] auto get_background_color() const -> const SDL_Color & { return clear_color_; }
        void set_background_color(SDL_Color const &color) { clear_color_ = color; }
        
    private:
        SDL_Renderer *renderer_ptr_ = nullptr;
        SDL_Window   *window_ptr_   = nullptr;
        SDL_Color    clear_color_   = {};
    };
}
