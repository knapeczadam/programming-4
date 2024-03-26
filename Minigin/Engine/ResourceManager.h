#pragma once

// Project includes
#include "game_font.h"
#include "Singleton.h"
#include "Texture2D.h"

// Standard includes
#include <memory>
#include <unordered_map>
#include <string>

namespace dae
{
    // Forward declarations
    // class Texture2D;
    // class Font;

    class resource_manager final : public singleton<resource_manager>
    {
    public:
        void init(const std::string& data_path);
        auto load_texture(const std::string& file) -> texture_2d*;
        auto load_font(const std::string& file, unsigned int size) -> game_font*;

    private:
        friend class singleton<resource_manager>;
        resource_manager() = default;
        std::string data_path_;

        std::unordered_map<std::string, std::unique_ptr<texture_2d>> textures_{};
        std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<game_font>>> fonts_{};
    };
}
