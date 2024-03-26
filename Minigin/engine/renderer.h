#pragma once

// Project includes
#include "singleton.h"

// SDL includes
#include <SDL.h>

namespace dae
{
    class texture_2d;
    /**
     * Simple RAII wrapper for the SDL renderer
     */
    class renderer final : public singleton<renderer>
    {
        SDL_Renderer* renderer_{};
        SDL_Window* window_{};
        SDL_Color clear_color_{};

    public:
        void init(SDL_Window* window);
        void render() const;
        void destroy();

        void render_texture(const texture_2d& texture, float x, float y) const;
        void render_texture(const texture_2d& texture, float x, float y, float width, float height) const;

        [[nodiscard]] auto get_sdl_renderer() const -> SDL_Renderer*;

        [[nodiscard]] auto get_background_color() const -> const SDL_Color& { return clear_color_; }
        void set_background_color(const SDL_Color& color) { clear_color_ = color; }
    };
}
