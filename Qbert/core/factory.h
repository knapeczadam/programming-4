#pragma once

// Standard includes
#include <string>
#include <vector>

// GLM includes
#include <optional>
#include <glm/glm.hpp>

// JSON includes
#include "json.hpp"

// Forward declarations
namespace mngn
{
    enum class multisprite_orientation;
    class game_font;
    class game_object;
    class scene;
    class collider_component;
    class sprite;

    enum input : int;
    enum class input_type;
    enum class input_state;
}

namespace qbert
{
    // Forward declarations
    class position_component;
    class health_component;
    class health_display_component;
    class level_display_component;
    class score_counter_component;
    class level_counter_component;
    class round_counter_component;
    class score_display_component;
    class round_display_component;
    class cube_component;
    class player_collider_component;
    
    // Aliases
    using json = nlohmann::json;
    
    struct factory
    {
        struct config_info
        {
            mngn::scene       *scene_ptr;
            mngn::game_object *parent_ptr;
            std::string       name;
            glm::vec2         local_position;
            int               texture_id;
            int               sprite_id;
        };

        struct info
        {
            mngn::game_object *go_ptr;
        };
        
        struct character
        {
            // Player
            struct player_config_info : config_info
            {
            private:
                struct command
                {
                    mngn::input_type  input_type;
                    mngn::input_state input_state;
                    mngn::input       input;
                };
                
            public:
                
                int                    row_idx;
                int                    col_idx;
                command                left_command;
                command                right_command;
                command                up_command;
                command                down_command;
                std::optional<command> left_command_alt;
                std::optional<command> right_command_alt;
                std::optional<command> up_command_alt;
                std::optional<command> down_command_alt;
            };

            struct player_info : info
            {
                position_component        *position_comp_ptr;
                health_component          *health_comp_ptr;
                score_counter_component   *score_counter_comp_ptr;
                level_counter_component   *level_counter_comp_ptr;
                round_counter_component   *round_counter_comp_ptr;
                player_collider_component *collider_comp_ptr;
            };

            static auto create_player(player_config_info const &config) -> player_info;
            static auto create_ai_player(player_config_info const &config) -> player_info;

            struct npc_info : info
            {
                position_component *position_comp_ptr;
                health_component   *health_comp_ptr;
            };

            // Red ball
            struct red_ball_config_info : config_info { };
            struct red_ball_info : npc_info
            {
            };
            static auto create_red_ball(red_ball_config_info const &config) -> red_ball_info;

            // Green ball
            struct green_ball_config_info : config_info { };
            struct green_ball_info : npc_info { };
            static auto create_green_ball(green_ball_config_info const &config) -> green_ball_info;

            // Coily
            struct coily_config_info : config_info { };
            struct coily_info : npc_info { };
            static auto create_coily(coily_config_info const &config) -> coily_info;

            // Ugg
            struct ugg_config_info : config_info { };
            struct ugg_info : npc_info { };
            static auto create_ugg(ugg_config_info const &config) -> ugg_info;

            // Wrong-way
            struct wrong_way_config_info : config_info { };
            struct wrong_way_info : npc_info { };
            static auto create_wrong_way(wrong_way_config_info const &config) -> wrong_way_info;

            // Slick
            struct slick_config_info : config_info { };
            struct slick_info : npc_info { };
            static auto create_slick(slick_config_info const &config) -> slick_info;

            // Sam
            struct sam_config_info : config_info { };
            struct sam_info : npc_info { };
            static auto create_sam(sam_config_info const &config) -> sam_info;
        };
        
        struct level
        {
            // Disk
            struct disk_config_info : config_info
            {
                int row_idx;
                int col_idx;
            };

            struct disk_info : info { };

            static auto create_disk(disk_config_info const &config) -> disk_info;

            // Cube
            struct cube_config_info : config_info
            {
                int                color_1;
                int                color_2;
                std::optional<int> color_3;
                int                cube_animated;
                bool               revertible;
                int                row_idx;
                int                col_idx;
            };

            struct cube_info : info
            {
                std::vector<cube_component*> cube_components;
            };

            static auto create_cubes(cube_config_info const &config) -> cube_info;
            static auto create_cube(cube_config_info const &config) -> cube_info;

            // Level
            struct level_config_info : config_info
            {
                int                 level_id;
                int                 round_id;
                int                 cube_color_1;
                int                 cube_color_2;
                std::optional<int>  cube_color_3;
                std::optional<bool> cube_revertible;
                int                 cube_color_small;
                int                 cube_animated;
                int                 cube_animated_small;
                int                 disk_count;
                int                 disk_color;
                json                disk_positions;
                cube_config_info    cube_config;
                disk_config_info    disk_config;
            };

            struct level_info
            {
                mngn::scene *scene_ptr;
                cube_info    cube_info;
            };
            static auto create_level(level_config_info const &config) -> level_info;
        };

        struct ui
        {
            // FPS
            struct fps_config_info : config_info
            {
                mngn::game_font *font_ptr;
                std::string     text;
            };

            struct fps_info : info { };

            static auto create_fps(fps_config_info const &config) -> fps_info;

            // Score display
            struct score_display_config_info : config_info { };
            
            struct score_display_info : info
            {
                score_display_component *score_display_comp_ptr;
            };

            static auto create_score_display(score_display_config_info const &config) -> score_display_info;

            // Health
            struct health_display_config_info : config_info { };

            struct health_display_info : info
            {
                health_display_component *health_display_comp_ptr;
            };

            static auto create_health_display(health_display_config_info const &config) -> health_display_info;

            // Level
            struct level_display_config_info : config_info { };

            struct level_display_info : info
            {
                level_display_component *level_display_comp_ptr;
            };

            static auto create_level_display(level_display_config_info const &config) -> level_display_info;

            // Round
            struct round_display_config_info : config_info { };

            struct round_display_info : info
            {
                round_display_component *round_display_comp_ptr;
            };

            // Small cube
            struct small_cube_config_info : config_info
            {
                int animated_sprite_id;
            };

            struct small_cube_info : info { };

            static auto create_small_cube(small_cube_config_info const &config) -> small_cube_info;

            static auto create_round_display(round_display_config_info const &config) -> round_display_info;

            // Sprite
            struct sprite_config_info : config_info
            {
                std::optional<int> curr_frame;
                bool               cached      = true;
            };


            struct sprite_info : info { };

            static auto create_sprite(sprite_config_info const &config) -> sprite_info;

            // Multisprite
            struct multisprite_config_info : config_info
            {
                std::vector<mngn::sprite*> sprites;
                std::optional<mngn::multisprite_orientation> orientation;
            };

            struct multisprite_info : info { };
            
            static auto create_multisprite(multisprite_config_info const &config) -> multisprite_info;

            // Arrow
            struct arrow_config_info : config_info
            {
                float delay;
            };

            struct arrow_info : info { };

            static auto create_arrow(arrow_config_info const &config) -> arrow_info;

            // Text
            struct text_config_info : config_info
            {
                std::string text;
                int          space_sprite_id;
                int          space_texture_id;
                int          exclamation_sprite_id;
                int          exclamation_texture_id;
                int          exclamation_frame;
                int          dot_sprite_id;
                int          dot_texture_id;
                int          dot_frame;
                int          at_sprite_id;
                int          at_texture_id;
                int          at_frame;
                int          equal_sprite_id;
                int          equal_texture_id;
                int          equal_frame;
                unsigned int spacing;
                
            };

            struct text_info : info { };

            static auto create_text(text_config_info const &config) -> text_info;
            static auto create_flickering_text(text_config_info const &config) -> text_info;

            // Number
            struct number_config_info : config_info
            {
                int number;
            };

            struct number_info : info { };

            static auto create_number(number_config_info const &config) -> number_info;
        };

    };
}
