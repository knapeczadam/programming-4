#include "resource_manager.h"

// Project includes
#include "renderer.h"
#include "minigin/utility/texture.h"
#include "minigin/utility/game_font.h"

// Standard includes
#include <fstream>
#include <stdexcept>

// SDL includes
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "minigin/sound/sound_effect.h"
#include "minigin/sound/sound_stream.h"

namespace mngn
{
    resource_manager::resource_manager() = default;
    
    resource_manager::~resource_manager() = default;

    void resource_manager::init(std::string const &data_path)
    {
        data_path_ = data_path;

        if (TTF_Init() != 0)
        {
            throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
        }
    }

    void resource_manager::load_resource_config()
    {
        std::ifstream file(data_path_ + resource_config_path_);
        if (file)
        {
            resource_config_ = json::parse(file);
        }
    }

    auto resource_manager::load_texture(std::string const &file_path) -> texture *
    {
        // Check if texture is already present
        auto const full_path = data_path_ + file_path;
        auto const it = textures_.find(full_path);
        if (it != textures_.cend())
        {
            return it->second.get();
        }
        
        auto texture_ptr = IMG_LoadTexture(renderer::instance().sdl_renderer(), full_path.c_str());
        if (texture_ptr == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
        }

        // Cache texture
        textures_[full_path] = std::make_unique<texture>(texture_ptr);
        return textures_[full_path].get();
    }

    auto resource_manager::load_texture(int id) -> texture *
    {
        std::string path;
        if (get_resource_path(id, path))
        {
            return load_texture(path);
        }
        return nullptr;
    }

    auto resource_manager::load_font(std::string const &file_path, unsigned int size) -> game_font *
    {
        // Check if font is already present
        auto const full_path = data_path_ + file_path;
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

    auto resource_manager::load_font(int id, unsigned int size) -> game_font *
    {
        std::string path;
        if (get_resource_path(id, path))
        {
            return load_font(path, size);
        }
        return nullptr;
    }

    auto resource_manager::get_sound_effect(int id) -> sound_effect *
    {
        std::string path;
        if (get_resource_path(id, path))
        {
            return load_sound_effect(path);
        }
        return nullptr;
    }

    auto resource_manager::get_sound_stream(int id) -> sound_stream *
    {
        std::string path;
        if (get_resource_path(id, path))
        {
            return load_sound_stream(path);
        }
        return nullptr;
    }

    auto resource_manager::add_resource_pair(int enum_id, std::string const &json_id) -> resource_manager &
    {
        resource_map_[enum_id] = json_id;
        return *this;
    }

    auto resource_manager::set_resource_config_path(std::string const &file_path) -> resource_manager &
    {
        resource_config_path_ = file_path;
        return *this;
    }

    auto resource_manager::load_sound_effect(std::string const &file_path) -> sound_effect *
    {
        // Check if sound effect is already present
        auto const full_path = data_path_ + file_path;
        auto const it = sound_effects_.find(full_path);
        if (it != sound_effects_.cend())
        {
            return it->second.get();
        }

        // Cache sound effect
        sound_effects_[full_path] = std::make_unique<sound_effect>(full_path);
        return sound_effects_[full_path].get();
    }

    auto resource_manager::load_sound_stream(std::string const &file_path) -> sound_stream *
    {
        // Check if sound stream is already present
        auto const full_path = data_path_ + file_path;
        auto const it = sound_streams_.find(full_path);
        if (it != sound_streams_.cend())
        {
            return it->second.get();
        }

        // Cache sound stream
        sound_streams_[full_path] = std::make_unique<sound_stream>(full_path);
        return sound_streams_[full_path].get();
    }

    auto resource_manager::get_resource_path(int id, std::string &file_path) -> bool
    {
        for (auto const& resource_config : resource_config_["resources"])
        {
            if (resource_config["id"] == to_string(id))
            {
                file_path = resource_config["path"];
                return true;
            }
        }
        return false;
    }

    auto resource_manager::to_string(int id) -> std::string const &
    {
        return resource_map_[id];
    }
}
