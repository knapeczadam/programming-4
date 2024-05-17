#include "factory.h"

// Project includes
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
#include "component/state/state_component.h"
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
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<state_component>();
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

        auto swearing_go_ptr = config.scene_ptr->create_game_object("swearing");
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
        info.go_ptr->add_tags({"npc", "enemy", "ball"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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
        info.go_ptr->add_tags({"npc", "friend", "ball"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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
        info.go_ptr->add_tags({"npc", "enemy", "ball"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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
        info.go_ptr->add_tags({"npc", "enemy"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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

    auto factory::character::create_wrong_way(wrong_way_config_info const &config) -> wrong_way_info
    {
        wrong_way_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "enemy"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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

    auto factory::character::create_slick(slick_config_info const &config) -> slick_info
    {
        slick_info info{};
        info.go_ptr = config.scene_ptr->create_game_object(config.name);
        info.go_ptr->add_tags({"npc", "friend"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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
        info.go_ptr->add_tags({"npc", "friend"});
        info.go_ptr->set_parent(config.parent_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<state_component>();
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
        info.score_display_comp_ptr = info.go_ptr->add_component<score_display_component>(config.sprite_id, config.texture_id);
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
        info.go_ptr->add_component<mngn::sprite_ui_component>(config.sprite_id, config.texture_id);
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
}
