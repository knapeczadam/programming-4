#include "factory.h"

// Project includes
#include "level_config_manager.h"
#include "sprites.h"
#include "component/level/cube_component.h"
#include "component/level/disk_component.h"
#include "component/level/fly_component.h"
#include "component/player/face_component.h"
#include "component/player/fall_component.h"
#include "component/player/player_health_component.h"
#include "component/npc/npc_health_component.h"
#include "component/character/jump_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/player_collider_component.h"
#include "component/state/character_state_component.h"
#include "component/character/position_component.h"
#include "component/player/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/player/swear_component.h"
#include "component/ui/flicker_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "component/character/direction_component.h"
#include "component/level/small_cube_component.h"
#include "component/npc/coily_component.h"
#include "component/npc/spawn_component.h"
#include "component/ui/alphabet_component.h"
#include "component/ui/number_component.h"
#include "input/game_object_commands.h"
#include "minigin/component/debug/fps_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    auto factory::character::create_player(player_config_info const &config) -> player_info
    {
        player_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("player");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<fall_component>();
        info.go_ptr->add_component<swear_component>();
        info.go_ptr->add_component<direction_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.position_comp_ptr      = info.go_ptr->add_component<position_component>(config.row_idx, config.col_idx);
        info.health_comp_ptr        = info.go_ptr->add_component<player_health_component>(4);
        info.score_counter_comp_ptr = info.go_ptr->add_component<score_counter_component>();
        info.level_counter_comp_ptr = info.go_ptr->add_component<level_counter_component>();
        info.round_counter_comp_ptr = info.go_ptr->add_component<round_counter_component>();
        info.collider_comp_ptr      = info.go_ptr->add_component<player_collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());

        auto swearing_go_ptr = config.scene_ptr->create_game_object(config.name + "_swearing");
        swearing_go_ptr->set_parent(info.go_ptr);
        swearing_go_ptr->set_local_position(-24.0f, -50.0f);
        swearing_go_ptr->add_component<mngn::sprite_component>(qb_sp_qbert_swearing, config.texture_id);
        swearing_go_ptr->add_tag("swearing");

        auto left_command = std::make_unique<jump_command>(info.go_ptr, -1, -1);
        auto right_command = std::make_unique<jump_command>(info.go_ptr, 1, 1);
        auto up_command = std::make_unique<jump_command>(info.go_ptr, -1, 0);
        auto down_command = std::make_unique<jump_command>(info.go_ptr, 1, 0);
        
    	mngn::input_config_info command_config{};
    	command_config.input_type     = config.left_command.input_type;
    	command_config.input_state    = config.left_command.input_state;
    	command_config.input          = config.left_command.input;
    	command_config.controller_idx = config.left_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(left_command));

        command_config.input_type     = config.right_command.input_type;
        command_config.input_state    = config.right_command.input_state;
        command_config.input          = config.right_command.input;
        command_config.controller_idx = config.right_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(right_command));

        command_config.input_type     = config.up_command.input_type;
        command_config.input_state    = config.up_command.input_state;
        command_config.input          = config.up_command.input;
        command_config.controller_idx = config.up_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(up_command));

        command_config.input_type     = config.down_command.input_type;
        command_config.input_state    = config.down_command.input_state;
        command_config.input          = config.down_command.input;
        command_config.controller_idx = config.down_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(down_command));

        if (config.left_command_alt)
        {
            auto left_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, -1);
            command_config.input_type     = config.left_command_alt.value().input_type;
            command_config.input_state    = config.left_command_alt.value().input_state;
            command_config.input          = config.left_command_alt.value().input;
            command_config.controller_idx = config.left_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(left_command_alt));
        }
        if (config.right_command_alt)
        {
            auto right_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 1);
            command_config.input_type     = config.right_command_alt.value().input_type;
            command_config.input_state    = config.right_command_alt.value().input_state;
            command_config.input          = config.right_command_alt.value().input;
            command_config.controller_idx = config.right_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(right_command_alt));
        }
        if (config.up_command_alt)
        {
            auto up_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, 0);
            command_config.input_type     = config.up_command_alt.value().input_type;
            command_config.input_state    = config.up_command_alt.value().input_state;
            command_config.input          = config.up_command_alt.value().input;
            command_config.controller_idx = config.up_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(up_command_alt));
        }
        if (config.down_command_alt)
        {
            auto down_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 0);
            command_config.input_type     = config.down_command_alt.value().input_type;
            command_config.input_state    = config.down_command_alt.value().input_state;
            command_config.input          = config.down_command_alt.value().input;
            command_config.controller_idx = config.down_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(down_command_alt));
        }

        return info;
    }

    auto factory::character::create_ai_player(player_config_info const &config) -> player_info
    {
        player_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"player", "ai"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<score_counter_component>();
        info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id, false);
        info.position_comp_ptr = info.go_ptr->add_component<position_component>(config.row_idx, config.col_idx);
        return info;
    }

    auto factory::character::create_red_ball(red_ball_config_info const &config) -> red_ball_info
    {
        red_ball_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "ball", "down"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        return info;
    }

    auto factory::character::create_green_ball(green_ball_config_info const &config) -> green_ball_info
    {
        green_ball_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "friend", "ball", "down"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        return info;
    }

    auto factory::character::create_coily(coily_config_info const &config) -> coily_info
    {
        coily_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "ball", "down", "coily_egg"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto coily_sprite_ptr = mngn::sprite_manager::instance().load_sprite(qb_sp_coily, config.texture_id);
        info.go_ptr->add_component<coily_component>(coily_sprite_ptr);
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        
        auto left_command = std::make_unique<jump_command>(info.go_ptr, -1, -1);
        auto right_command = std::make_unique<jump_command>(info.go_ptr, 1, 1);
        auto up_command = std::make_unique<jump_command>(info.go_ptr, -1, 0);
        auto down_command = std::make_unique<jump_command>(info.go_ptr, 1, 0);
        
    	mngn::input_config_info command_config{};
    	command_config.input_type     = config.left_command.input_type;
    	command_config.input_state    = config.left_command.input_state;
    	command_config.input          = config.left_command.input;
    	command_config.controller_idx = config.left_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(left_command));

        command_config.input_type     = config.right_command.input_type;
        command_config.input_state    = config.right_command.input_state;
        command_config.input          = config.right_command.input;
        command_config.controller_idx = config.right_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(right_command));

        command_config.input_type     = config.up_command.input_type;
        command_config.input_state    = config.up_command.input_state;
        command_config.input          = config.up_command.input;
        command_config.controller_idx = config.up_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(up_command));

        command_config.input_type     = config.down_command.input_type;
        command_config.input_state    = config.down_command.input_state;
        command_config.input          = config.down_command.input;
        command_config.controller_idx = config.down_command.controller_idx;
        mngn::input_manager::instance().bind_command(command_config, std::move(down_command));

        if (config.left_command_alt)
        {
            auto left_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, -1);
            command_config.input_type     = config.left_command_alt.value().input_type;
            command_config.input_state    = config.left_command_alt.value().input_state;
            command_config.input          = config.left_command_alt.value().input;
            command_config.controller_idx = config.left_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(left_command_alt));
        }
        if (config.right_command_alt)
        {
            auto right_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 1);
            command_config.input_type     = config.right_command_alt.value().input_type;
            command_config.input_state    = config.right_command_alt.value().input_state;
            command_config.input          = config.right_command_alt.value().input;
            command_config.controller_idx = config.right_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(right_command_alt));
        }
        if (config.up_command_alt)
        {
            auto up_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, 0);
            command_config.input_type     = config.up_command_alt.value().input_type;
            command_config.input_state    = config.up_command_alt.value().input_state;
            command_config.input          = config.up_command_alt.value().input;
            command_config.controller_idx = config.up_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(up_command_alt));
        }
        if (config.down_command_alt)
        {
            auto down_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 0);
            command_config.input_type     = config.down_command_alt.value().input_type;
            command_config.input_state    = config.down_command_alt.value().input_state;
            command_config.input          = config.down_command_alt.value().input;
            command_config.controller_idx = config.down_command_alt.value().controller_idx;
            mngn::input_manager::instance().bind_command(command_config, std::move(down_command_alt));
        }
        
        return info;
    }

    auto factory::character::create_ugg(ugg_config_info const &config) -> ugg_info
    {
        ugg_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "right", "position_offset"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>(6, 6);
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        return info;
    }

    auto factory::character::create_wrong_way(wrong_way_config_info const &config) -> wrong_way_info
    {
        wrong_way_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "left", "position_offset"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>(6, 0);
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        return info;
    }

    auto factory::character::create_slick(slick_config_info const &config) -> slick_info
    {
        slick_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "friend", "down"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<npc_health_component>(1);
        return info;
    }

    auto factory::character::create_sam(sam_config_info const &config) -> sam_info
    {
        sam_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "friend", "down"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        auto sprite_ptr = sprite_comp_ptr->sprite();
        info.go_ptr->add_component<mngn::collider_component>(sprite_ptr->collider_width(), sprite_ptr->collider_height(), sprite_ptr->collider_offset_x(), sprite_ptr->collider_offset_y());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
        return info;
    }

    auto factory::level::create_disk(disk_config_info const &config) -> disk_info
    {
        disk_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("level");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id, false);
        info.go_ptr->add_component<disk_component>(config.row_idx, config.col_idx);
        info.go_ptr->add_component<fly_component>();
        info.go_ptr->add_tag("disk");

        return info;
    }

    auto factory::level::create_cubes(cube_config_info const &config) -> cube_info
    {
        cube_info info{};

        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;

        cube_config_info cube_config{};
        cube_config = config;

        std::vector<cube_component*> cube_components;
        for (int i = 0; i < 7; ++i)
        {
            glm::vec2 start_position = origin + glm::vec2(i * offset_x, i * offset_y);
            for (int j = 0; j < i + 1; ++j)
            {
                cube_config.name = config.scene_id + "cube_" + std::to_string(i) + "_" + std::to_string(j);
                glm::vec2 pos = start_position + glm::vec2(j * 64, 0);
                cube_config.local_position = pos;
                cube_config.row_idx = i;
                cube_config.col_idx = j;
                auto cube_info = create_cube(cube_config);
                cube_components.push_back(cube_info.go_ptr->component<cube_component>());
            }
        }

        info.cube_components = cube_components;
        return info;
    }

    auto factory::level::create_cube(cube_config_info const &config) -> cube_info
    {
        cube_info info{};
        mngn::sprite *color_1_sprite_ptr  = nullptr;
        mngn::sprite *color_2_sprite_ptr  = nullptr;
        mngn::sprite *color_3_sprite_ptr  = nullptr;
        mngn::sprite *animated_sprite_ptr = nullptr;
        
        color_1_sprite_ptr = mngn::sprite_manager::instance().load_sprite(config.color_1, config.texture_id);
        color_2_sprite_ptr = mngn::sprite_manager::instance().load_sprite(config.color_2, config.texture_id);
        if (config.cube_animated)
        {
            animated_sprite_ptr = mngn::sprite_manager::instance().load_sprite(config.cube_animated, config.texture_id, false);
        }
        if (config.color_3)
        {
            color_3_sprite_ptr = mngn::sprite_manager::instance().load_sprite(config.color_3.value(), config.texture_id);
        }
        
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_component>();
        info.go_ptr->add_tags({"level", "cube"});

        cube_component_config_info cube_comp_info{};
        cube_comp_info.row_idx    = config.row_idx;
        cube_comp_info.col_idx    = config.col_idx;
        cube_comp_info.revertible = config.revertible;
        cube_comp_info.animated_sprite_ptr = animated_sprite_ptr;
        
        if (color_3_sprite_ptr)
        {
            cube_comp_info.colors = {color_1_sprite_ptr, color_2_sprite_ptr, color_3_sprite_ptr};
            info.go_ptr->add_component<cube_component>(cube_comp_info);
        }
        else
        {
            cube_comp_info.colors = {color_1_sprite_ptr, color_2_sprite_ptr};
            info.go_ptr->add_component<cube_component>(cube_comp_info);
        }

        return info;
    }

    auto factory::level::create_level(level_config_info const &config) -> level_info
    {
        level_info info{};
        info.scene_ptr = config.scene_ptr;
        cube_config_info cube_config{};
        cube_config.scene_ptr  = config.scene_ptr;
        cube_config.parent_ptr = config.parent_ptr;
        cube_config.scene_id   = config.scene_id;
        cube_config.texture_id = config.cube_config.texture_id;
        cube_config.color_1    = config.cube_color_1;
        cube_config.color_2    = config.cube_color_2;
        if (config.cube_color_3) cube_config.color_3 = config.cube_color_3.value();
        if (config.cube_revertible) cube_config.revertible = config.cube_revertible.value();
        cube_config.cube_animated = config.cube_animated;
        info.cube_info = create_cubes(cube_config);

        ui::small_cube_config_info small_cube_config{};
        small_cube_config.scene_ptr  = config.scene_ptr;
        small_cube_config.parent_ptr = config.parent_ptr;
        small_cube_config.name       = config.scene_id + "small_cube";
        small_cube_config.local_position = {64.0f, 96.0f};
        small_cube_config.sprite_id = config.cube_color_small;
        small_cube_config.animated_sprite_id = config.cube_animated_small;
        small_cube_config.texture_id = config.texture_id;
        ui::create_small_cube(small_cube_config);

        int num_of_disks = config.disk_count;
        for (int i = 0; i < num_of_disks; ++i)
        {
            disk_config_info disk_config{};
            disk_config.scene_ptr  = config.scene_ptr;
            disk_config.parent_ptr = config.parent_ptr;
            disk_config.name       = config.scene_id + "disk_" + std::to_string(i);
            disk_config.sprite_id  = config.disk_color;
            disk_config.texture_id = config.disk_config.texture_id;

            auto disk_positions = config.disk_positions;
            disk_config.row_idx  = disk_positions[i * 2];
            disk_config.col_idx  = disk_positions[i * 2 + 1];
            create_disk(disk_config);
        }
        return info;
    }

    auto factory::ui::create_fps(fps_config_info const &config) -> fps_info
    {
        fps_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        auto fps_comp_ptr = info.go_ptr->add_component<mngn::fps_component>();
        fps_comp_ptr->set_font(config.font_ptr);
        fps_comp_ptr->set_text(config.text);
        return info;
    }

    auto factory::ui::create_score_display(score_display_config_info const &config) -> score_display_info
    {
        score_display_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::multisprite_ui_component>();
        info.go_ptr->add_component<number_component>(0, config.sprite_id, config.texture_id);
        info.score_display_comp_ptr = info.go_ptr->add_component<score_display_component>();
        return info;
    }

    auto factory::ui::create_health_display(health_display_config_info const &config) -> health_display_info
    {
        health_display_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::multisprite_ui_component>(mngn::multisprite_orientation::vertical);
        info.health_display_comp_ptr = info.go_ptr->add_component<health_display_component>();
        return info;
    }

    auto factory::ui::create_level_display(level_display_config_info const &config) -> level_display_info
    {
        level_display_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id, false);
        info.level_display_comp_ptr = info.go_ptr->add_component<level_display_component>();
        return info;
    }

    auto factory::ui::create_small_cube(small_cube_config_info const &config) -> small_cube_info
    {
        small_cube_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<small_cube_component>(config.animated_sprite_id, config.texture_id);
        return info;
    }

    auto factory::ui::create_round_display(round_display_config_info const &config) -> round_display_info
    {
        round_display_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id, false);
        info.round_display_comp_ptr = info.go_ptr->add_component<round_display_component>();
        return info;
    }

    auto factory::ui::create_sprite(sprite_config_info const &config) -> sprite_info
    {
        sprite_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        auto sprite_ui_comp_ptr = info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id, config.cached);
        if (config.curr_frame) sprite_ui_comp_ptr->sprite()->set_current_frame(config.curr_frame.value());
        return info;
    }

    auto factory::ui::create_multisprite(multisprite_config_info const &config) -> multisprite_info
    {
        multisprite_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        if (config.orientation)
        {
            auto multisprite_ui_comp_ptr = info.go_ptr->add_component<mngn::multisprite_ui_component>(config.orientation.value());
            multisprite_ui_comp_ptr->set_sprites(config.sprites);
        }
        else
        {
            auto multisprite_ui_comp_ptr = info.go_ptr->add_component<mngn::multisprite_ui_component>();
            multisprite_ui_comp_ptr->set_sprites(config.sprites);
        }
        return info;
    }

    auto factory::ui::create_arrow(arrow_config_info const &config) -> arrow_info
    {
        arrow_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<flicker_component>(config.delay);
        return info;
    }

    auto factory::ui::create_text(text_config_info const &config) -> text_info
    {
        alphabet_config_info alphabet_config{};
        alphabet_config.text                   = config.text;
        alphabet_config.sprite_id              = config.sprite_id;
        alphabet_config.texture_id             = config.texture_id;
        alphabet_config.space_sprite_id        = config.space_sprite_id;
        alphabet_config.space_texture_id       = config.space_texture_id;
        alphabet_config.exclamation_sprite_id  = config.exclamation_sprite_id;
        alphabet_config.exclamation_texture_id = config.exclamation_texture_id;
        alphabet_config.exclamation_frame      = config.exclamation_frame;
        alphabet_config.dot_sprite_id          = config.dot_sprite_id;
        alphabet_config.dot_texture_id         = config.dot_texture_id;
        alphabet_config.dot_frame              = config.dot_frame;
        alphabet_config.at_sprite_id           = config.at_sprite_id;
        alphabet_config.at_texture_id          = config.at_texture_id;
        alphabet_config.at_frame               = config.at_frame;
        alphabet_config.equal_sprite_id        = config.equal_sprite_id;
        alphabet_config.equal_texture_id       = config.equal_texture_id;
        alphabet_config.equal_frame            = config.equal_frame;
        alphabet_config.hyphen_sprite_id       = config.hyphen_sprite_id;
        alphabet_config.hyphen_texture_id      = config.hyphen_texture_id;
        alphabet_config.hyphen_frame           = config.hyphen_frame;
        
        text_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::multisprite_ui_component>(mngn::multisprite_orientation::horizontal, config.spacing);
        info.go_ptr->add_component<alphabet_component>(alphabet_config);
        return info;
    }

    auto factory::ui::create_flickering_text(text_config_info const &config) -> text_info
    {
        auto info = create_text(config);
        info.go_ptr->add_component<flicker_component>();
        return info;
    }

    auto factory::ui::create_number(number_config_info const &config) -> number_info
    {
        number_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::multisprite_ui_component>();
        info.go_ptr->add_component<number_component>(config.number, config.sprite_id, config.texture_id);
        return info;
    }
}
