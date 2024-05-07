#include "texture_2d.h"

// SDL includes
#include <SDL.h>

namespace mngn
{
    texture_2d::~texture_2d()
    {
        SDL_DestroyTexture(texture_ptr_);
    }

    auto texture_2d::get_size() const -> glm::ivec2
    {
        SDL_Rect dst;
        SDL_QueryTexture(get_sdl_texture(), nullptr, nullptr, &dst.w, &dst.h);
        return {dst.w, dst.h};
    }

    auto texture_2d::get_sdl_texture() const -> SDL_Texture *
    {
        return texture_ptr_;
    }

    texture_2d::texture_2d(SDL_Texture *texture_ptr)
    {
        texture_ptr_ = texture_ptr;
    }
}
