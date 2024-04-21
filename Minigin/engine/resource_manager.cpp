#include "resource_manager.h"

// Project includes
#include "renderer.h"
#include "utility/texture_2d.h"
#include "utility/game_font.h"

// Standard includes
#include <stdexcept>

// SDL includes
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace dae
{
    void resource_manager::init(std::string const &data_path)
    {
        data_path_ = data_path;

        if (TTF_Init() != 0)
        {
            throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
        }
    }

    auto resource_manager::load_texture(std::string const &file) -> texture_2d *
    {
        // Check if texture is already present
        auto const full_path = data_path_ + file;
        auto const it = textures_.find(full_path);
        if (it != textures_.cend())
        {
            return it->second.get();
        }
        
        auto texture = IMG_LoadTexture(renderer::get_instance().get_sdl_renderer(), full_path.c_str());
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
        }

        // Cache the texture
        textures_[full_path] = std::make_unique<texture_2d>(texture);
        return textures_[full_path].get();
    }

    auto resource_manager::load_font(std::string const &file, unsigned int size) -> game_font *
    {
        // Check if font is already present
        auto const full_path = data_path_ + file;
        auto const range = fonts_.equal_range(full_path);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second.first == size)
            {
                return it->second.second.get();
            }
        }

        // Load the font and cache it
        auto font = std::make_unique<game_font>(full_path, size);
        fonts_.emplace(full_path, std::make_pair(size, std::move(font)));

        // Return the newly loaded font
        auto const [fst, snd] = fonts_.equal_range(full_path);
        for (auto it = fst; it != snd; ++it)
        {
            if (it->second.first == size)
            {
                return it->second.second.get();
            }
        }
        return nullptr;
    }
}
