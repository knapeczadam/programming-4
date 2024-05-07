#include "resource_manager.h"

// Project includes
#include "renderer.h"
#include "minigin/utility/texture_2d.h"
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

        init_resource_ids();
        load_resource_config();
    }

    void resource_manager::init_resource_ids()
    {
        resource_ids_[resource_id::e_qbert_fall] = "e_qbert_fall";
        resource_ids_[resource_id::e_qbert_jump] = "e_qbert_jump";
    }

    void resource_manager::load_resource_config()
    {
        std::ifstream file(data_path_ + "config/resource_config.json");
        if (file)
        {
            resource_config_ = json::parse(file);
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

        // Cache texture
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

    auto resource_manager::get_sound_effect(resource_id id) -> sound_effect *
    {
        for (auto const& sound : resource_config_["sounds"])
        {
            auto const effects = sound["effects"];
            for (auto const& effect : effects)
            {
                if (effect["id"] == to_string(id))
                {
                    return load_sound_effect(effect["file"]);
                }
            }
        }
        return nullptr;
    }

    auto resource_manager::get_sound_stream(resource_id id) -> sound_stream *
    {
        for (auto const& stream : resource_config_["sounds"]["streams"])
        {
            if (stream["id"] == to_string(id))
            {
                return load_sound_stream(stream["file"]);
            }
        }
        return nullptr;
    }

    auto resource_manager::load_sound_effect(std::string const &file) -> sound_effect *
    {
        // Check if sound effect is already present
        auto const full_path = data_path_ + "sound/effect/" + file;
        auto const it = sound_effects_.find(full_path);
        if (it != sound_effects_.cend())
        {
            return it->second.get();
        }

        // Cache sound effect
        sound_effects_[full_path] = std::make_unique<sound_effect>(full_path);
        return sound_effects_[full_path].get();
    }

    auto resource_manager::load_sound_stream(std::string const &file) -> sound_stream *
    {
        // Check if sound stream is already present
        auto const full_path = data_path_ + "sound/stream/" + file;
        auto const it = sound_streams_.find(full_path);
        if (it != sound_streams_.cend())
        {
            return it->second.get();
        }

        // Cache sound stream
        sound_streams_[full_path] = std::make_unique<sound_stream>(full_path);
        return sound_streams_[full_path].get();
    }

    auto resource_manager::to_string(resource_id id) -> std::string const &
    {
        return resource_ids_[id];
    }
}
