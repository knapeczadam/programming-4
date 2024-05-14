// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "component/player/position_idx_component.h"
#include "component/player/health_component.h"
#include "component/level/level_counter_component.h"
#include "component/level/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "component/player/jump_component.h"
#include "component/level/cube_component.h"
#include "component/level/level_manager_component.h"
#include "component/player/player_state_component.h"
#include "core/factory.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/generic_commands.h"
#include "ui/ui.h"

#include "minigin/component/debug/fps_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/engine.h"
#include "minigin/core/game_object.h"
#include "minigin/core/resource_manager.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"
#include "minigin/services/logging_sound_system.h"
#include "minigin/services/sdl_sound_system.h"
#include "minigin/services/service_locator.h"
#include "minigin/test/test_manager.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <cassert>
#include <iostream>

// SDL includes
#include <SDL.h>

void register_services()
{
#ifndef _NDEBUG
	mngn::service_locator::register_sound_system(std::make_unique<mngn::logging_sound_system>(std::make_unique<mngn::sdl_sound_system>()));
#else
	dae::service_locator::register_sound_system(std::make_unique<dae::sdl_sound_system>());
#endif
}

void load()
{
    using namespace mngn;
	using namespace qbert;

	register_services();
	
	init_resources();
	init_sprites();
	
	// load_test_level();
	load_test_ui();

    auto const scene = scene_manager::instance().create_scene("Demo");
    
    // Fonts
    auto const font_small = resource_manager::instance().load_font("fonts/Lingua.otf", 10);

    // FPS
    auto go = scene->add_game_object();
    go->set_local_position(10.0f, 500.0f);
    auto const fps_comp = go->add_component<fps_component>();
    fps_comp->set_font(font_small);
    fps_comp->set_text("FPS: ");
	
	auto root_go_ptr = scene->add_game_object("root");
	auto level_manager_comp_ptr = root_go_ptr->add_component<level_manager_component>();
	
	glm::vec2 origin{208, 96};
	int offset_x = -32;
	int offset_y = 48;
	
	auto color_1 = sprite_manager::instance().load_sprite(qb_sp_level_1_red_cube_1, qb_re_t_sprite_general);
	auto color_2 = sprite_manager::instance().load_sprite(qb_sp_level_1_yellow_cube_1, qb_re_t_sprite_general);
	auto color_3 = sprite_manager::instance().load_sprite(qb_sp_level_1_blue_cube_1, qb_re_t_sprite_general);

	std::vector<cube_component*> cubes;
	for (int i = 0; i < 7; ++i)
	{
		glm::vec2 start_position = origin + glm::vec2(i * offset_x, i * offset_y);
		for (int j = 0; j < i + 1; ++j)
		{
			go = scene->add_game_object("cube_" + std::to_string(i) + "_" + std::to_string(j));
			glm::vec2 pos = start_position + glm::vec2(j * 64, 0);
			go->set_local_position(pos);
			go->add_component<sprite_component>();
			auto cube_comp_ptr = go->add_component<cube_component>(i, j, std::vector{color_1, color_2, color_3});
			cubes.push_back(cube_comp_ptr);
		}
	}
	
	go = scene->add_game_object("score_1");
	go->set_local_position(32, 48);
	go->add_component<multisprite_ui_component>();
	auto score_display_comp_ptr = go->add_component<score_display_component>();
        
	go = scene->add_game_object("qbert_life_1");
	go->set_local_position(16, 160);
	go->add_component<multisprite_ui_component>(multisprite_orientation::vertical);
	auto health_display_comp_ptr = go->add_component<health_display_component>();
	
	go = scene->add_game_object("numbers_level");
	go->set_local_position(432, 80);
	go->add_component<sprite_ui_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general, false);
	auto level_display_comp_ptr = go->add_component<level_display_component>();

	go = scene->add_game_object("numbers_round");
	go->set_local_position(432, 96);
	go->add_component<sprite_ui_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general, false);
	auto round_display_comp_ptr = go->add_component<round_display_component>();

	go = scene->add_game_object("player");
	auto level_comp_ptr = go->add_component<level_counter_component>();
	level_comp_ptr->add_observer(level_display_comp_ptr);
	auto round_comp_ptr = go->add_component<round_counter_component>();
	round_comp_ptr->add_observer(round_display_comp_ptr);

	//---------------------------------------------------------------------------------
	// DISCS
	//---------------------------------------------------------------------------------
	factory::level::disc_config_info disc_config;
	disc_config.scene_ptr = scene;
	disc_config.parent_go_ptr = root_go_ptr;
	disc_config.name = "disc_1";
	disc_config.sprite_id = qb_sp_level_1_disk_1;
	disc_config.texture_id = qb_re_t_sprite_general;
	disc_config.row_idx = 6;
	disc_config.col_idx = -1;
	factory::level::create_disc(disc_config);

	factory::level::disc_config_info disc_config_2;
	disc_config_2.scene_ptr = scene;
	disc_config_2.parent_go_ptr = root_go_ptr;
	disc_config_2.name = "disc_2";
	disc_config_2.sprite_id = qb_sp_level_1_disk_2;
	disc_config_2.texture_id = qb_re_t_sprite_general;
	disc_config_2.row_idx = 2;
	disc_config_2.col_idx = 3;
	factory::level::create_disc(disc_config_2);
	
    //---------------------------------------------------------------------------------
    // PLAYER 1
    //---------------------------------------------------------------------------------
	factory::character::player_config_info player_1_config;
	player_1_config.scene_ptr         = scene;
	player_1_config.parent_go_ptr     = root_go_ptr;
	player_1_config.name              = "player_1";
	player_1_config.local_position    = {224.0f,                 84.0f};
	player_1_config.sprite_id         = qb_sp_qbert_1;
	player_1_config.texture_id        = qb_re_t_sprite_general;
	player_1_config.row_idx           = 0;
	player_1_config.col_idx           = 0;
	player_1_config.left_command      = {input_type::keyboard,   input_state::down,    k_left};
	player_1_config.right_command     = {input_type::keyboard,   input_state::down,    k_right};
	player_1_config.up_command        = {input_type::keyboard,   input_state::down,    k_up};
	player_1_config.down_command      = {input_type::keyboard,   input_state::down,    k_down};
	player_1_config.left_command_alt  = {input_type::controller, input_state::pressed, c_left};
	player_1_config.right_command_alt = {input_type::controller, input_state::pressed, c_right};
	player_1_config.up_command_alt    = {input_type::controller, input_state::pressed, c_up};
	player_1_config.down_command_alt  = {input_type::controller, input_state::pressed, c_down};
	
	auto player_1_info = factory::character::create_player(player_1_config);
	player_1_info.health_comp_ptr->add_observer(health_display_comp_ptr);
    player_1_info.score_counter_comp_ptr->add_observer(score_display_comp_ptr);
	player_1_info.position_idx_comp_ptr->add_observer(level_manager_comp_ptr);
	std::ranges::for_each(cubes, [player_1_info](auto cube) { player_1_info.position_idx_comp_ptr->add_observer(cube); });

    //---------------------------------------------------------------------------------
    // PLAYER 2
    //---------------------------------------------------------------------------------
	factory::character::player_config_info player_2_config;
	player_2_config.scene_ptr      = scene;
	player_2_config.parent_go_ptr  = root_go_ptr;
	player_2_config.name           = "player_2";
	player_2_config.local_position = {32.0f,                 372.0f};
	player_2_config.sprite_id      = qb_sp_qbert_2;
	player_2_config.texture_id     = qb_re_t_sprite_general;
	player_2_config.row_idx        = 6;
	player_2_config.col_idx        = 0;
	player_2_config.left_command   = {input_type::keyboard,  input_state::down, k_a};
	player_2_config.right_command  = {input_type::keyboard,  input_state::down, k_d};
	player_2_config.up_command     = {input_type::keyboard,  input_state::down, k_w};
	player_2_config.down_command   = {input_type::keyboard,  input_state::down, k_s};
	auto player_2_info = factory::character::create_player(player_2_config);
	
    player_2_info.health_comp_ptr->add_observer(health_display_comp_ptr);
	player_2_info.score_counter_comp_ptr->add_observer(score_display_comp_ptr);
	player_2_info.position_idx_comp_ptr->add_observer(level_manager_comp_ptr);
	std::ranges::for_each(cubes, [player_2_info](auto cube) { player_2_info.position_idx_comp_ptr->add_observer(cube); });

	//---------------------------------------------------------------------------------
	// DEBUG
	//---------------------------------------------------------------------------------
	auto debug_command_ptr = std::make_unique<debug_command>(round_comp_ptr);
	input_manager::instance().bind_command(input_type::keyboard, input_state::down, k_j, std::move(debug_command_ptr));
}

int main(int, char *[])
{
    mngn::engine engine("../Data/");
	
#ifndef NDEBUG
    mngn::test_manager::instance().run_all_tests();
#endif
	
    engine.run(load);
	
    return 0;
}
