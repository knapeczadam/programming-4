#include "factory.h"

// Project includes
#include "level_config_manager.h"
#include "sprites.h"
#include "component/level/cube_component.h"
#include "component/level/disc_component.h"
#include "component/level/fly_component.h"
#include "component/player/face_component.h"
#include "component/player/fall_component.h"
#include "component/player/health_component.h"
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
        info.position_comp_ptr      = info.go_ptr->add_component<position_component>(config.row_idx, config.col_idx);
        info.health_comp_ptr        = info.go_ptr->add_component<health_component>(3);
        info.score_counter_comp_ptr = info.go_ptr->add_component<score_counter_component>();
        info.level_counter_comp_ptr = info.go_ptr->add_component<level_counter_component>();
        info.round_counter_comp_ptr = info.go_ptr->add_component<round_counter_component>();
        info.collider_comp_ptr      = info.go_ptr->add_component<player_collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());

        auto swearing_go_ptr = config.scene_ptr->create_game_object(config.name + "_swearing");
        swearing_go_ptr->set_parent(info.go_ptr);
        swearing_go_ptr->set_local_position(-24.0f, -50.0f);
        swearing_go_ptr->add_component<mngn::sprite_component>(qb_sp_qbert_swearing, config.texture_id);

        auto left_command = std::make_unique<jump_command>(info.go_ptr, -1, -1);
        auto right_command = std::make_unique<jump_command>(info.go_ptr, 1, 1);
        auto up_command = std::make_unique<jump_command>(info.go_ptr, -1, 0);
        auto down_command = std::make_unique<jump_command>(info.go_ptr, 1, 0);

        mngn::input_manager::instance().bind_command(config.left_command.input_type, config.left_command.input_state, config.left_command.input, std::move(left_command));
        mngn::input_manager::instance().bind_command(config.right_command.input_type, config.right_command.input_state, config.right_command.input, std::move(right_command));
        mngn::input_manager::instance().bind_command(config.up_command.input_type, config.up_command.input_state, config.up_command.input, std::move(up_command));
        mngn::input_manager::instance().bind_command(config.down_command.input_type, config.down_command.input_state, config.down_command.input, std::move(down_command));

        if (config.left_command_alt)
        {
            auto left_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, -1);
            mngn::input_manager::instance().bind_command(config.left_command_alt.value().input_type, config.left_command_alt.value().input_state, config.left_command_alt.value().input, std::move(left_command_alt));
        }
        if (config.right_command_alt)
        {
            auto right_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 1);
            mngn::input_manager::instance().bind_command(config.right_command_alt.value().input_type, config.right_command_alt.value().input_state, config.right_command_alt.value().input, std::move(right_command_alt));
        }
        if (config.up_command_alt)
        {
            auto up_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, 0);
            mngn::input_manager::instance().bind_command(config.up_command_alt.value().input_type, config.up_command_alt.value().input_state, config.up_command_alt.value().input, std::move(up_command_alt));
        }
        if (config.down_command_alt)
        {
            auto down_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 0);
            mngn::input_manager::instance().bind_command(config.down_command_alt.value().input_type, config.down_command_alt.value().input_state, config.down_command_alt.value().input, std::move(down_command_alt));
        }

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
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
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
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
        return info;
    }

    auto factory::character::create_coily(coily_config_info const &config) -> coily_info
    {
        coily_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "ball", "down"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
        return info;
    }

    auto factory::character::create_ugg(ugg_config_info const &config) -> ugg_info
    {
        ugg_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "right"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>(6, 6);
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
        return info;
    }

    auto factory::character::create_wrong_way(wrong_way_config_info const &config) -> wrong_way_info
    {
        wrong_way_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy", "left"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<character_state_component>();
        info.go_ptr->add_component<direction_component>();
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<spawn_component>();
        info.go_ptr->add_component<fall_component>();
        auto sprite_comp_ptr = info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>(6, 0);
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
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
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
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
        info.go_ptr->add_component<mngn::collider_component>(sprite_comp_ptr->sprite()->collider_width(), sprite_comp_ptr->sprite()->collider_height());
        info.position_comp_ptr = info.go_ptr->add_component<position_component>();
        info.health_comp_ptr   = info.go_ptr->add_component<health_component>(1);
        return info;
    }

    auto factory::level::create_disc(disc_config_info const &config) -> disc_info
    {
        disc_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("level");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<disc_component>(config.row_idx, config.col_idx);
        info.go_ptr->add_component<fly_component>();

        return info;
    }

    auto factory::level::create_cubes(cube_config_info const &config) -> cube_info
    {
        cube_info info{};

        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;

        mngn::sprite *color_1 = nullptr;
        mngn::sprite *color_2 = nullptr;
        mngn::sprite *color_3 = nullptr;

        color_1 = mngn::sprite_manager::instance().load_sprite(config.color_1, config.texture_id);
        color_2 = mngn::sprite_manager::instance().load_sprite(config.color_2, config.texture_id);
        if (config.color_3)
        {
            color_3 = mngn::sprite_manager::instance().load_sprite(config.color_3.value(), config.texture_id);
        }

        std::vector<cube_component*> cube_components;
        for (int i = 0; i < 7; ++i)
        {
            glm::vec2 start_position = origin + glm::vec2(i * offset_x, i * offset_y);
            for (int j = 0; j < i + 1; ++j)
            {
                auto go = config.scene_ptr->create_game_object("cube_" + std::to_string(i) + "_" + std::to_string(j));
                go->add_tag("level");
                go->set_parent(config.parent_ptr);
                
                glm::vec2 pos = start_position + glm::vec2(j * 64, 0);
                go->set_local_position(pos);
                go->add_component<mngn::sprite_component>();

                cube_component *cube_comp_ptr = nullptr;
                if (color_3)
                {
                    cube_comp_ptr = go->add_component<cube_component>(i, j, std::vector{color_1, color_2, color_3}, config.revertible);
                }
                else
                {
                    cube_comp_ptr = go->add_component<cube_component>(i, j, std::vector{color_1, color_2}, config.revertible);
                }
                
                cube_components.push_back(cube_comp_ptr);
            }
        }

        info.cube_components = cube_components;
        return info;
    }

    auto factory::level::create_level(level_config_info const &config) -> level_info
    {
        level_info info{};
        info.scene_ptr = config.scene_ptr;
        
        for (auto const &level_config : config.level_config["levels"])
        {
            if (level_config["level_id"] == config.level_id and level_config["round_id"] == config.round_id)
            {
                cube_config_info cube_config{};
                cube_config.scene_ptr  = config.scene_ptr;
                cube_config.parent_ptr = config.parent_ptr;
                cube_config.texture_id = config.cube_config.texture_id;
                cube_config.color_1    = level_config["cube_color_1"];
                cube_config.color_2    = level_config["cube_color_2"];
                if (level_config.contains("cube_color_3")) cube_config.color_3 = level_config["cube_color_3"];
                if (level_config.contains("cube_revertible")) cube_config.revertible = level_config["cube_revertible"];
                info.cube_info = create_cubes(cube_config);

                ui::sprite_config_info sprite_config{};
                sprite_config.scene_ptr      = config.scene_ptr;
                sprite_config.parent_ptr     = config.parent_ptr;
                sprite_config.name           = "cube_color_small";
                sprite_config.local_position = {64, 96};
                sprite_config.sprite_id      = level_config["cube_color_small"];
                ui::create_sprite(sprite_config);

                int num_of_disks = level_config["disk_count"];
                for (int i = 0; i < num_of_disks; ++i)
                {
                    disc_config_info disc_config{};
                    disc_config.scene_ptr  = config.scene_ptr;
                    disc_config.parent_ptr = config.parent_ptr;
                    disc_config.name       = "disc_" + std::to_string(i);
                    disc_config.sprite_id  = level_config["disk_color"];
                    disc_config.texture_id = config.disc_config.texture_id;

                    auto disk_positions = level_config["disk_positions"];
                    disc_config.row_idx  = disk_positions[i * 2];
                    disc_config.col_idx  = disk_positions[i * 2 + 1];
                    create_disc(disc_config);
                }
            }
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
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id);
        info.level_display_comp_ptr = info.go_ptr->add_component<level_display_component>();
        return info;
    }

    auto factory::ui::create_round_display(round_display_config_info const &config) -> round_display_info
    {
        round_display_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tag("ui");
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id);
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
