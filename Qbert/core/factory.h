#pragma once

// Standard includes
#include <string>
#include <vector>

// GLM includes
#include <optional>
#include <glm/glm.hpp>

// Forward declarations
namespace mngn
{
    class game_font;
    class game_object;
    class scene;

    enum input : int;
    enum class input_type;
    enum class input_state;
}

namespace qbert
{
    // Forward declarations
    enum qbert_resource : int;
    enum qbert_sprite   : int;
    
    
    class position_idx_component;
    class health_component;
    class health_display_component;
    class level_display_component;
    class score_counter_component;
    class level_counter_component;
    class round_counter_component;
    class score_display_component;
    class round_display_component;
    class cube_component;
    
    struct factory
    {
        struct config_info
        {
            mngn::scene       *scene_ptr;
            mngn::game_object *parent_ptr;
            std::string       name;
            glm::vec2         local_position;
            qbert_resource    texture_id;
            qbert_sprite      sprite_id;
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
                position_idx_component  *position_idx_comp_ptr;
                health_component        *health_comp_ptr;
                score_counter_component *score_counter_comp_ptr;
                level_counter_component *level_counter_comp_ptr;
                round_counter_component *round_counter_comp_ptr;
            };
            
            static auto create_player(player_config_info const& config) -> player_info;
        };
        
        struct level
        {
            // Disc
            struct disc_config_info : config_info
            {
                int               row_idx;
                int               col_idx;
            };

            struct disc_info : info { };

            static auto create_disc(disc_config_info const& config) -> disc_info;

            // Cube
            struct cube_config_info : config_info
            {
                qbert_sprite                color_1;
                qbert_sprite                color_2;
                std::optional<qbert_sprite> color_3;
                bool                        revertible;
            };

            struct cube_info : info
            {
                std::vector<cube_component*> cube_components;
            };

            static auto create_cubes(cube_config_info const& config) -> cube_info;
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

            static auto create_fps(fps_config_info const& config) -> fps_info;

            // Score display
            struct score_display_config_info : config_info { };
            
            struct score_display_info : info
            {
                score_display_component *score_display_comp_ptr;
            };

            static auto create_score_display(score_display_config_info const& config) -> score_display_info;

            // Health
            struct health_display_config_info : config_info { };

            struct health_display_info : info
            {
                health_display_component *health_display_comp_ptr;
            };

            static auto create_health_display(health_display_config_info const& config) -> health_display_info;

            // Level
            struct level_display_config_info : config_info { };

            struct level_display_info : info
            {
                level_display_component *level_display_comp_ptr;
            };

            static auto create_level_display(level_display_config_info const& config) -> level_display_info;

            // Round
            struct round_display_config_info : config_info { };

            struct round_display_info : info
            {
                round_display_component *round_display_comp_ptr;
            };

            static auto create_round_display(round_display_config_info const& config) -> round_display_info;

            // Sprite
            struct sprite_config_info : config_info { };

            struct sprite_info : info { };

            static auto create_sprite(sprite_config_info const& config) -> sprite_info;

            // Arrow
            struct arrow_config_info : config_info
            {
                float delay;
            };

            struct arrow_info : info { };

            static auto create_arrow(arrow_config_info const& config) -> arrow_info;
        };
    };
}
