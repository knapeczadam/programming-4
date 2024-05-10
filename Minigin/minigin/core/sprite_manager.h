#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <vector>

// JSON includes
#include "json.hpp"

namespace mngn
{
    // Forward declarations
    class texture;
    class sprite;
    
    // Aliases
    using json = nlohmann::json;

    class sprite_manager final : public singleton<sprite_manager>
    {
    public:
        ~sprite_manager() override;

        sprite_manager(const sprite_manager &other)            = delete;
        sprite_manager(sprite_manager &&other)                 = delete;
        sprite_manager &operator=(const sprite_manager &other) = delete;
        sprite_manager &operator=(sprite_manager &&other)      = delete;

        auto set_data_path(std::string const &data_path) -> sprite_manager &;
        auto set_sprite_config_path(std::string const &sprite_config_path) -> sprite_manager &;
        void load_sprite_config();
        auto load_sprite(int sprite_id, int texture_id) -> sprite *;
        
        auto add_sprite_pair(int enum_id, std::string const &json_id) -> sprite_manager &;

    private:
        auto create_sprite(int id, texture* texture_ptr) -> sprite *;
        auto to_string(int id) -> std::string const &;

    private:
        friend class singleton<sprite_manager>;
        sprite_manager();

    private:
        std::string data_path_;
        std::string sprite_config_path_;
        json sprite_config_;
        // std::vector<std::unique_ptr<sprite>> sprites_;
        std::unordered_map<int, std::unique_ptr<sprite>> sprites_;
        
        std::unordered_map<int, std::string> sprite_map_;
    };
}
