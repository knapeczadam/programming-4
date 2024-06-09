#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <unordered_map>

// JSON includes
#include "json.hpp"

namespace mngn
{
    // Forward declarations
    class texture;
    class sprite;
    class game_font;
    class sound_effect;
    class sound_stream;

    // Aliases
    using json = nlohmann::json;

    class resource_manager final : public singleton<resource_manager>
    {
    public:
        ~resource_manager() override;

        resource_manager(resource_manager const& other)            = delete;
        resource_manager(resource_manager &&other)                 = delete;
        resource_manager &operator=(resource_manager const &other) = delete;
        resource_manager &operator=(resource_manager &&other)      = delete;
        
        void init(std::string const &data_path);
        void load_resource_config();
        auto load_texture(std::string const &file_path) -> texture *;
        auto load_texture(int id) -> texture *;
        
        auto load_font(std::string const &file_path, unsigned int size) -> game_font *;
        auto load_font(int id, unsigned int size) -> game_font *;
        
        [[nodiscard]] auto get_sound_effect(int id) -> sound_effect *;
        [[nodiscard]] auto get_sound_stream(int id) -> sound_stream *;

        auto register_resource(int enum_id, std::string const &json_id) -> resource_manager &;
        auto set_resource_config_path(std::string const &file_path) -> resource_manager &;

    private:
        auto load_sound_effect(std::string const& file_path) -> sound_effect *;
        auto load_sound_stream(std::string const& file_path) -> sound_stream *;
        auto get_resource_path(int id, std::string &file_path) -> bool;

        auto to_string(int id) -> std::string const &;

    private:
        friend class singleton<resource_manager>;
        resource_manager();

    private:
        std::string data_path_;
        std::string resource_config_path_;
        json        resource_config_;

        std::unordered_map<std::string, std::unique_ptr<texture>>                              textures_;
        std::unordered_map<std::string, std::unique_ptr<sound_effect>>                            sound_effects_;
        std::unordered_map<std::string, std::unique_ptr<sound_stream>>                            sound_streams_;
        std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<game_font>>> fonts_;

        std::unordered_map<int, std::string> resource_map_;
    };
}
