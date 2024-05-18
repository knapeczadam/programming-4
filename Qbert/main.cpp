// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "component/level/cube_component.h"
#include "component/level/level_manager_component.h"
#include "component/player/health_component.h"
#include "component/character/jump_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/player_collider_component.h"
#include "component/character/position_component.h"
#include "component/player/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "core/factory.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/generic_commands.h"

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

// Standard includes
#include <cassert>
#include <iostream>

// SDL includes
#include <SDL.h>

#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/level_config_manager.h"


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

	//---------------------------------------------------------------------------------
	// RESOURCES
	//---------------------------------------------------------------------------------
	init_resources();
	init_sprites();

	//---------------------------------------------------------------------------------
	// FONTS
	//---------------------------------------------------------------------------------
    auto const font_small = resource_manager::instance().load_font("fonts/Lingua.otf", 10);

	//---------------------------------------------------------------------------------
	// TEST SCENE
	//---------------------------------------------------------------------------------
    auto const scene = scene_manager::instance().create_scene("Demo");
	scene->set_active(false);
    
	//---------------------------------------------------------------------------------
	// ROOT
	//---------------------------------------------------------------------------------
	auto root_ptr = scene->create_game_object("game");
	auto level_manager_comp_ptr = root_ptr->add_component<level_manager_component>();
	root_ptr->add_component<game_state_component>();


	// ---------------------------------------------------------------------------------
	// LEVEL
	//---------------------------------------------------------------------------------
	level_config_manager::instance().load_level_config("../Data/configs/level_config.json");
	factory::level::level_config_info level_config{};
	level_config.scene_ptr = scene;
	level_config.parent_ptr = root_ptr;
	level_config.level_id = 1;
	level_config.level_config = level_config_manager::instance().get_level_config();
	auto level_info = factory::level::create_level(level_config);

	//---------------------------------------------------------------------------------
    // FPS
	//---------------------------------------------------------------------------------
	factory::ui::fps_config_info fps_config{};
	fps_config.scene_ptr      = scene;
	fps_config.parent_ptr     = root_ptr;
	fps_config.name           = "fps";
	fps_config.local_position = {10.0f,      500.0f};
	fps_config.font_ptr       = font_small;
	fps_config.text		      = "FPS: ";
	factory::ui::create_fps(fps_config);

	//---------------------------------------------------------------------------------
	// UI
	//---------------------------------------------------------------------------------
	factory::ui::score_display_config_info score_display_config{};
	score_display_config.scene_ptr      = scene;
	score_display_config.parent_ptr     = root_ptr;
	score_display_config.name           = "score_1";
	score_display_config.local_position = {32.0f,    48.0f};
	score_display_config.sprite_id	  = qb_sp_numbers_regular_orange;
	score_display_config.texture_id     = qb_re_t_sprite_general;
	auto score_display_info_1 = factory::ui::create_score_display(score_display_config);
	
	score_display_config.name           = "score_2";
	score_display_config.sprite_id	  = qb_sp_numbers_regular_purple;
	score_display_config.local_position = {332.0f,    48.0f};
	auto score_display_info_2 = factory::ui::create_score_display(score_display_config);

	factory::ui::health_display_config_info health_display_config{};
	health_display_config.scene_ptr      = scene;
	health_display_config.parent_ptr     = root_ptr;
	health_display_config.name           = "health_1";
	health_display_config.local_position = {16.0f, 160.0f};
	auto heal_display_info_1 = factory::ui::create_health_display(health_display_config);
	
	health_display_config.name           = "health_1";
	health_display_config.local_position = {448.0f, 160.0f};
	auto heal_display_info_2 = factory::ui::create_health_display(health_display_config);

	factory::ui::level_display_config_info level_display_config{};
	level_display_config.scene_ptr      = scene;
	level_display_config.parent_ptr     = root_ptr;
	level_display_config.name           = "numbers_level";
	level_display_config.local_position = {432.0f, 80.0f};
	level_display_config.sprite_id      = qb_sp_numbers_regular_orange;
	level_display_config.texture_id     = qb_re_t_sprite_general;
	auto level_display_info = factory::ui::create_level_display(level_display_config);

	factory::ui::round_display_config_info round_display_config{};
	round_display_config.scene_ptr      = scene;
	round_display_config.parent_ptr     = root_ptr;
	round_display_config.name           = "round_1";
	round_display_config.local_position = {432.0f, 96.0f};
	round_display_config.sprite_id      = qb_sp_numbers_regular_orange;
	round_display_config.texture_id     = qb_re_t_sprite_general;
	auto round_display_info = factory::ui::create_round_display(round_display_config);

	factory::ui::text_config_info text_config{};
	text_config.scene_ptr      = scene;
	text_config.parent_ptr     = root_ptr;
	text_config.name           = "text_1";
	text_config.local_position = {176.0f, 288.0f};
	text_config.sprite_id      = qb_sp_alphabet_regular_purple;
	text_config.texture_id     = qb_re_t_sprite_general;
	text_config.space_sprite_id = qb_sp_alphabet_regular_space;
	text_config.space_texture_id = qb_re_t_sprite_general;
	text_config.text           = "game over";
	factory::ui::create_flickering_text(text_config);

    //---------------------------------------------------------------------------------
    // PLAYER 1
    //---------------------------------------------------------------------------------
	factory::character::player_config_info player_1_config{};
	player_1_config.scene_ptr         = scene;
	player_1_config.parent_ptr        = root_ptr;
	player_1_config.name              = "player_1";
	player_1_config.local_position    = {224.0f, 84.0f};
	player_1_config.sprite_id         = qb_sp_qbert_player_1;
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
	// Observers
	auto player_1_info = factory::character::create_player(player_1_config);
	collision_manager::instance().register_collider(player_1_info.collider_comp_ptr);
	player_1_info.health_comp_ptr->add_observer(heal_display_info_1.health_display_comp_ptr);
	player_1_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
    player_1_info.score_counter_comp_ptr->add_observer(score_display_info_1.score_display_comp_ptr);
	player_1_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	player_1_info.level_counter_comp_ptr->add_observer(level_display_info.level_display_comp_ptr);
	player_1_info.round_counter_comp_ptr->add_observer(round_display_info.round_display_comp_ptr);
	std::ranges::for_each(level_info.cube_info.cube_components, [player_1_info](auto cube_comp_ptr) { player_1_info.position_comp_ptr->add_observer(cube_comp_ptr); });

    //---------------------------------------------------------------------------------
    // PLAYER 2
    //---------------------------------------------------------------------------------
	factory::character::player_config_info player_2_config{};
	player_2_config.scene_ptr      = scene;
	player_2_config.parent_ptr  = root_ptr;
	player_2_config.name           = "player_2";
	player_2_config.local_position = {32.0f, 372.0f};
	player_2_config.sprite_id      = qb_sp_qbert_player_2;
	player_2_config.texture_id     = qb_re_t_sprite_general;
	player_2_config.row_idx        = 6;
	player_2_config.col_idx        = 0;
	player_2_config.left_command   = {input_type::keyboard,  input_state::down, k_a};
	player_2_config.right_command  = {input_type::keyboard,  input_state::down, k_d};
	player_2_config.up_command     = {input_type::keyboard,  input_state::down, k_w};
	player_2_config.down_command   = {input_type::keyboard,  input_state::down, k_s};
	// Observers
	auto player_2_info = factory::character::create_player(player_2_config);
    player_2_info.health_comp_ptr->add_observer(heal_display_info_2.health_display_comp_ptr);
    player_2_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
	player_2_info.score_counter_comp_ptr->add_observer(score_display_info_2.score_display_comp_ptr);
	player_2_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	std::ranges::for_each(level_info.cube_info.cube_components, [player_2_info](auto cube_comp_ptr) { player_2_info.position_comp_ptr->add_observer(cube_comp_ptr); });

	//---------------------------------------------------------------------------------
	// ENEMY
	//---------------------------------------------------------------------------------
	// Red Ball
	factory::character::red_ball_config_info red_ball_config{};
	red_ball_config.scene_ptr      = scene;
	red_ball_config.parent_ptr     = root_ptr;
	red_ball_config.name           = "red_ball_1";
	red_ball_config.sprite_id	   = qb_sp_ball_red;
	red_ball_config.texture_id     = qb_re_t_sprite_general;
	auto red_ball_info = factory::character::create_red_ball(red_ball_config);
	// Observers
	red_ball_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	red_ball_info.health_comp_ptr->add_observer(level_manager_comp_ptr);

	// Coily
	factory::character::coily_config_info coily_config{};
	coily_config.scene_ptr      = scene;
	coily_config.parent_ptr     = root_ptr;
	coily_config.name           = "coily_1";
	coily_config.sprite_id	   = qb_sp_coily_egg;
	coily_config.texture_id     = qb_re_t_sprite_general;
	auto coily_info = factory::character::create_coily(coily_config);
	// Observers
	coily_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	coily_info.health_comp_ptr->add_observer(level_manager_comp_ptr);

	// Ugg
	factory::character::ugg_config_info ugg_config{};
	ugg_config.scene_ptr      = scene;
	ugg_config.parent_ptr     = root_ptr;
	ugg_config.name           = "ugg_1";
	ugg_config.sprite_id	   = qb_sp_ugg;
	ugg_config.texture_id     = qb_re_t_sprite_general;
	auto ugg_info = factory::character::create_ugg(ugg_config);
	// Observers
	ugg_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	ugg_info.health_comp_ptr->add_observer(level_manager_comp_ptr);

	// Wrong-Way
	factory::character::wrong_way_config_info wrong_way_config{};
	wrong_way_config.scene_ptr      = scene;
	wrong_way_config.parent_ptr     = root_ptr;
	wrong_way_config.name           = "wrong_way_1";
	wrong_way_config.sprite_id	   = qb_sp_wrong_way;
	wrong_way_config.texture_id     = qb_re_t_sprite_general;
	auto wrong_way_info = factory::character::create_wrong_way(wrong_way_config);
	// Observers
	wrong_way_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	wrong_way_info.health_comp_ptr->add_observer(level_manager_comp_ptr);

	//---------------------------------------------------------------------------------
	// FRIENDS
	//---------------------------------------------------------------------------------
	// Green Ball
	factory::character::green_ball_config_info green_ball_config{};
	green_ball_config.scene_ptr  = scene;
	green_ball_config.parent_ptr = root_ptr;
	green_ball_config.name       = "green_ball_1";
	green_ball_config.sprite_id  = qb_sp_ball_green;
	green_ball_config.texture_id = qb_re_t_sprite_general;
	auto green_ball_info = factory::character::create_green_ball(green_ball_config);
	// Observers
	green_ball_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	green_ball_info.health_comp_ptr->add_observer(level_manager_comp_ptr);

	// Slick
	factory::character::slick_config_info slick_config{};
	slick_config.scene_ptr  = scene;
	slick_config.parent_ptr = root_ptr;
	slick_config.name       = "slick_1";
	slick_config.sprite_id  = qb_sp_slick;
	slick_config.texture_id = qb_re_t_sprite_general;
	auto slick_info = factory::character::create_slick(slick_config);
	// Observers
	slick_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	slick_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
	std::ranges::for_each(level_info.cube_info.cube_components, [slick_info](auto cube_comp_ptr) { slick_info.position_comp_ptr->add_observer(cube_comp_ptr); });

	// Sam
	factory::character::sam_config_info sam_config{};
	sam_config.scene_ptr  = scene;
	sam_config.parent_ptr = root_ptr;
	sam_config.name       = "sam_1";
	sam_config.sprite_id  = qb_sp_sam;
	sam_config.texture_id = qb_re_t_sprite_general;
	auto sam_info = factory::character::create_sam(sam_config);
	// Observers
	sam_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
	sam_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
	std::ranges::for_each(level_info.cube_info.cube_components, [sam_info](auto cube_comp_ptr) { sam_info.position_comp_ptr->add_observer(cube_comp_ptr); });

	//---------------------------------------------------------------------------------
	// DEBUG
	//---------------------------------------------------------------------------------
	auto debug_command_ptr = std::make_unique<debug_command>();
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
