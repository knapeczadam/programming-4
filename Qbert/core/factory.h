#pragma once

// Standard includes
#include <string>

// GLM includes
#include <optional>
#include <glm/glm.hpp>

// Forward declarations
namespace mngn
{
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
    class score_counter_component;
    
    struct factory
    {
        struct character
        {
            
            struct player_config_info
            {
            private:
                struct command
                {
                    mngn::input_type  input_type;
                    mngn::input_state input_state;
                    mngn::input       input;
                };
                
            public:
                
                mngn::scene            *scene_ptr;
                mngn::game_object      *parent_go_ptr;
                std::string            name;
                glm::vec2              local_position;
                qbert_sprite           sprite_id;
                qbert_resource         texture_id;
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

            struct player_info
            {
                mngn::game_object       *go_ptr;
                position_idx_component  *position_idx_comp_ptr;
                health_component        *health_comp_ptr;
                score_counter_component *score_counter_comp_ptr;
            };
            
            static auto create_player(player_config_info const& config) -> player_info;
        };
        
        struct level
        {
            
        };

        struct my_struct
        {
            
        };
    };
}
