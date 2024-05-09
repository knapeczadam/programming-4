#include "texture.h"

// SDL includes
#include <SDL.h>

namespace mngn
{
    texture::~texture()
    {
        SDL_DestroyTexture(texture_ptr_);
    }

    auto texture::get_size() const -> glm::ivec2
    {
        SDL_Rect dst;
        SDL_QueryTexture(get_sdl_texture(), nullptr, nullptr, &dst.w, &dst.h);
        return {dst.w, dst.h};
    }

    auto texture::get_width() const -> int
    {
        return get_size().x;
    }

    auto texture::get_height() const -> int
    {
        return get_size().y;
    }

    auto texture::get_sdl_texture() const -> SDL_Texture *
    {
        return texture_ptr_;
    }

    texture::texture(SDL_Texture *texture_ptr)
    {
        texture_ptr_ = texture_ptr;
    }
}
