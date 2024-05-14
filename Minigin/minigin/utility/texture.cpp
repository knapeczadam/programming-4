#include "texture.h"

// SDL includes
#include <SDL.h>

namespace mngn
{
    texture::texture(SDL_Texture *texture_ptr)
        : texture_ptr_{texture_ptr}
    {
    }
    
    texture::~texture()
    {
        SDL_DestroyTexture(texture_ptr_);
    }

    auto texture::size() const -> glm::ivec2
    {
        SDL_Rect dst;
        SDL_QueryTexture(sdl_texture(), nullptr, nullptr, &dst.w, &dst.h);
        return {dst.w, dst.h};
    }
}
