#pragma once

// Project includes
#include "utility/singleton.h"

// Standard includes
#include <memory>
#include <unordered_map>
#include <string>

// JSON includes
#include "json.hpp"

namespace dae
{
    // Forward declarations
    class texture_2d;
    class game_font;
    class sound_effect;
    class sound_stream;

    // Aliases
    using json = nlohmann::json;
    
    enum class resource_id
    {
        // --- IMAGES ---

        // --- SOUNDS ---

        // Effects
        e_qbert_fall,
        e_qbert_jump

        // Streams
    };


    class resource_manager final : public singleton<resource_manager>
    {
    public:
        ~resource_manager() override;

        resource_manager(resource_manager const& other)            = delete;
        resource_manager(resource_manager &&other)                 = delete;
        resource_manager &operator=(resource_manager const &other) = delete;
        resource_manager &operator=(resource_manager &&other)      = delete;
        
        void init(std::string const &data_path);
        void init_resource_ids();
        void load_resource_config();
        auto load_texture(std::string const &file) -> texture_2d *;
        auto load_font(std::string const &file, unsigned int size) -> game_font *;
        
        [[nodiscard]] auto get_sound_effect(resource_id id) -> sound_effect *;
        [[nodiscard]] auto get_sound_stream(resource_id id) -> sound_stream *;

    private:
        auto load_sound_effect(std::string const& file) -> sound_effect *;
        auto load_sound_stream(std::string const& file) -> sound_stream *;

        auto to_string(resource_id id) -> std::string const &;

    private:
        friend class singleton<resource_manager>;
        resource_manager();
        std::string data_path_;
        json resource_config_;

        std::unordered_map<std::string, std::unique_ptr<texture_2d>>                              textures_;
        std::unordered_map<std::string, std::unique_ptr<sound_effect>>                            sound_effects_;
        std::unordered_map<std::string, std::unique_ptr<sound_stream>>                            sound_streams_;
        std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<game_font>>> fonts_;

        std::unordered_map<resource_id, std::string> resource_ids_;
    };
}
