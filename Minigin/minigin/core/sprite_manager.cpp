﻿#include "sprite_manager.h"

// Project includes
#include "minigin/core/resource_manager.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <fstream>
#include <iostream>

namespace mngn
{
    sprite_manager::sprite_manager() = default;
    sprite_manager::~sprite_manager() = default;

    auto sprite_manager::set_data_path(std::string const &data_path) -> sprite_manager &
    {
        data_path_ = data_path;
        return *this;
    }

    auto sprite_manager::set_sprite_config_path(std::string const &sprite_config_path) -> sprite_manager &
    {
        sprite_config_path_ = sprite_config_path;
        return *this;
    }

    void sprite_manager::load_sprite_config()
    {
        std::ifstream file(data_path_ + sprite_config_path_);
        if (file)
        {
            sprite_config_ = json::parse(file);
        }
    }

    auto sprite_manager::load_sprite(int sprite_id, int texture_id, bool cache) -> sprite *
    {
        if (cache and cached_sprites_.contains(sprite_id))
        {
            return cached_sprites_[sprite_id].get();
        }
        
        auto texture_ptr = resource_manager::instance().load_texture(texture_id);
        return create_sprite(sprite_id, texture_ptr, cache);
    }

    auto sprite_manager::create_sprite(int id, texture * texture_ptr, bool cache) -> sprite *
    {
        std::unique_ptr<sprite> new_sprite = nullptr;
        for (auto const &sprite_config : sprite_config_["sprites"])
        {
            if (sprite_config["id"] == to_string(id))
            {
                new_sprite = std::make_unique<sprite>(texture_ptr);

                if (sprite_config.contains("rows"))                new_sprite->set_rows(sprite_config["rows"]);
                if (sprite_config.contains("columns"))             new_sprite->set_cols(sprite_config["columns"]);
                if (sprite_config.contains("sub_rows"))            new_sprite->set_sub_rows(sprite_config["sub_rows"]);
                if (sprite_config.contains("sub_columns"))         new_sprite->set_sub_cols(sprite_config["sub_columns"]);
                if (sprite_config.contains("left_offset_pixel"))   new_sprite->set_left_offset_px(sprite_config["left_offset_pixel"]);
                if (sprite_config.contains("left_offset_columns")) new_sprite->set_left_offset_cols(sprite_config["left_offset_columns"]);
                if (sprite_config.contains("top_offset_pixel"))    new_sprite->set_top_offset_px(sprite_config["top_offset_pixel"]);
                if (sprite_config.contains("top_offset_rows"))     new_sprite->set_top_offset_rows(sprite_config["top_offset_rows"]);
                if (sprite_config.contains("collider_width"))      new_sprite->set_collider_width(sprite_config["collider_width"]);
                if (sprite_config.contains("collider_height"))     new_sprite->set_collider_height(sprite_config["collider_height"]);
                if (sprite_config.contains("collider_offset_x"))   new_sprite->set_collider_offset_x(sprite_config["collider_offset_x"]);
                if (sprite_config.contains("collider_offset_y"))   new_sprite->set_collider_offset_y(sprite_config["collider_offset_y"]);
                if (sprite_config.contains("frames_per_second"))   new_sprite->set_frames_per_sec(sprite_config["frames_per_second"]);
                if (sprite_config.contains("scale"))               new_sprite->set_scale(sprite_config["scale"]);
                if (sprite_config.contains("clip_width"))          new_sprite->set_clip_width(sprite_config["clip_width"]);
                if (sprite_config.contains("clip_height"))         new_sprite->set_clip_height(sprite_config["clip_height"]);

                new_sprite->init();
                
                if (sprite_config.contains("current_frame"))              new_sprite->set_current_frame(sprite_config["current_frame"]);

                sprite *sprite_ptr = new_sprite.get();
                if (cache)
                {
                    cached_sprites_[id] = std::move(new_sprite);
                }
                else
                {
                    sprites_.emplace(id, std::move(new_sprite));
                }
                return sprite_ptr;
            }
        }
        if (new_sprite == nullptr)
        {
            std::cerr << "* sprite_manager::load_sprite - Sprite id \"" << to_string(id) << "\" not found in sprite_map_. Use \'add_sprite_pair\'!\n";
        }
        return nullptr;
    }

    auto sprite_manager::register_sprite(int enum_id, std::string const &json_id) -> sprite_manager &
    {
        sprite_map_[enum_id] = json_id;
        return *this;
    }

    auto sprite_manager::to_string(int id) -> std::string const &
    {
        return sprite_map_[id];
    }
}
