﻿#include "scene_loader.h"

// Project includes
#include "component/character/jump_component.h"
#include "component/character/health_component.h"
#include "component/character/position_component.h"
#include "component/level/cube_component.h"
#include "component/level/level_manager_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/player_collider_component.h"
#include "component/player/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "core/factory.h"
#include "core/level_config_manager.h"
#include "core/resources.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "core/sprites.h"
#include "input/game_component_commands.h"
#include "input/generic_commands.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/resource_manager.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"
#include "minigin/utility/random.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <ranges>

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    void scene_loader::load_scenes()
    {
#ifndef NDEBUG
    	load_debug_scene();
#endif
        load_menu_scenes();
        load_loading_scene();
        load_single_scenes();
        load_coop_scenes();
        load_versus_scenes();
        load_game_over_scene();
        load_scoreboard_scene();
    	load_input_scene();
    	load_game_state_scene();
    	bind_generic_commands();
    }

	void scene_loader::load_scenes(const std::string &scene_name, std::function<void(scene_info)> &&load_scene_func)
	{
    	int bonus_start = 1000;
	    int constexpr bonus_increment = 250;
    	auto config_file = level_config_manager::instance().level_config();
        for (auto const &level_config : config_file["levels"])
        {
        	auto level_id = to_string(level_config["level_id"]);
        	auto round_id = to_string(level_config["round_id"]);
        	
			auto const scene_ptr = mngn::scene_manager::instance().create_scene(scene_name + "_" + level_id + "_" + round_id);
			scene_ptr->set_active(false);
        	
			auto const root_ptr = scene_ptr->create_game_object("root");
			auto const level_manager_comp_ptr = root_ptr->add_component<level_manager_component>();
        	
			scene_info scene_info{};
			scene_info.scene_ptr              = scene_ptr;
			scene_info.root_ptr               = root_ptr;
			scene_info.level_manager_comp_ptr = level_manager_comp_ptr;
			scene_info.level_config           = level_config;
			scene_info.scene_id               = scene_name + "_" + level_id + "_" + round_id + "_";
			scene_info.bonus                  = bonus_start;
        	load_scene_func(scene_info);

        	bonus_start += bonus_increment;
        }
	}

    void scene_loader::load_debug_scene()
    {
		auto const font_ptr = mngn::resource_manager::instance().load_font("fonts/Lingua.otf", 10);
		auto const scene_ptr = mngn::scene_manager::instance().create_scene("debug");
		factory::ui::fps_config_info fps_config{};
		fps_config.scene_ptr      = scene_ptr;
		fps_config.name           = "fps";
		fps_config.local_position = {10.0f, 500.0f};
		fps_config.font_ptr       = font_ptr;
		fps_config.text		      = "FPS: ";
		factory::ui::create_fps(fps_config);
    	
    	mngn::input_config_info key_config{};
    	key_config.input_type  = mngn::input_type::keyboard;
    	key_config.input_state = mngn::input_state::down;
    	key_config.input       = mngn::input::k_j;
    	
		auto debug_command_ptr = std::make_unique<debug_command>();
		mngn::input_manager::instance().bind_command(key_config, std::move(debug_command_ptr));
    }

    void scene_loader::load_game_state_scene()
    {
		auto const scene_ptr = mngn::scene_manager::instance().create_scene("game_state");
	    auto const go_ptr = scene_ptr->create_game_object("game_state");
	    go_ptr->add_component<game_state_component>();
    }

    void scene_loader::load_menu_scenes()
    {
    	load_menu_scene();
    	load_menu_scene_1();
    	load_menu_scene_2();
    	load_menu_scene_3();
    }

    void scene_loader::load_menu_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("menu");
        scene_ptr->set_active(false);
    	
        factory::ui::text_config_info text_config{};
        text_config.scene_ptr              = scene_ptr;
        text_config.name                   = "text_credits";
        text_config.local_position         = {336, 64};
    	text_config.text                   = "credits";
    	text_config.sprite_id              = qb_sp_alphabet_regular_green;
    	text_config.texture_id             = qb_re_t_sprite_general;
    	text_config.space_sprite_id        = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id       = qb_re_t_sprite_general;
    	text_config.exclamation_sprite_id  = qb_sp_alphabet_regular_special;
    	text_config.exclamation_texture_id = qb_re_t_sprite_general;
    	text_config.exclamation_frame      = 3;
        factory::ui::create_text(text_config);
    	
        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr;
        number_config.name           = "coin";
    	number_config.local_position = {432.0f, 80.0f};
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
    	number_config.number         = 0;
    	auto number_info = factory::ui::create_number(number_config);
    	number_info.go_ptr->add_tag("coin");
    	
        text_config.name           = "game_modes";
        text_config.local_position = {32, 464};
        text_config.text           = "single     coop     versus";
        text_config.sprite_id      = qb_sp_alphabet_bold_orange;
        factory::ui::create_text(text_config);

    	std::vector<mngn::sprite*> sprites;
    	std::generate_n(std::back_inserter(sprites), 6, []
		{
			auto const sprite_ptr =  mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general, false);
			sprite_ptr->set_current_frame(11);
    		return sprite_ptr;	
		});

    	factory::ui::multisprite_config_info multisprite_config{};
    	multisprite_config.scene_ptr      = scene_ptr;
    	multisprite_config.name           = "underline_single";
    	multisprite_config.local_position = {32.0f, 480.0f};
    	multisprite_config.sprites		  = sprites;
    	auto multisprite_info = factory::ui::create_multisprite(multisprite_config);
    	multisprite_info.go_ptr->add_component<flicker_component>();
    	multisprite_info.go_ptr->add_tag("active");
    	
    	multisprite_config.name           = "underline_versus";
    	multisprite_config.local_position = {352.0f, 480.0f};
    	multisprite_config.sprites		  = sprites;
    	multisprite_info = factory::ui::create_multisprite(multisprite_config);
    	multisprite_info.go_ptr->add_component<flicker_component>();
    	multisprite_info.go_ptr->set_active(false);

		sprites.clear();
    	std::generate_n(std::back_inserter(sprites), 4, []
		{
			auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general, false);
			sprite_ptr->set_current_frame(11);
    		return sprite_ptr;	
		});
    	multisprite_config.name           = "underline_coop";
    	multisprite_config.local_position = {208.0f, 480.0f};
    	multisprite_config.sprites		  = sprites;
    	multisprite_info = factory::ui::create_multisprite(multisprite_config);
    	multisprite_info.go_ptr->add_component<flicker_component>();
    	multisprite_info.go_ptr->set_active(false);
    }
	
    void scene_loader::load_menu_scene_1()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("menu_1");
        scene_ptr->set_active(false);
        
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "text_qbert";
        sprite_config.local_position = {158, 192};
        sprite_config.sprite_id      = qb_sp_text_qbert;
        factory::ui::create_sprite(sprite_config);

        factory::ui::text_config_info text_config{};
        text_config.scene_ptr              = scene_ptr;
        text_config.name                   = "row_1";
        text_config.local_position         = {48, 240};
    	text_config.text                   = "credits";
        text_config.text                   = "@     d. gottlieb and co.";
    	text_config.sprite_id              = qb_sp_alphabet_regular_green;
    	text_config.texture_id             = qb_re_t_sprite_general;
    	text_config.space_sprite_id        = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id       = qb_re_t_sprite_general;
    	text_config.dot_sprite_id		   = qb_sp_alphabet_regular_special;
    	text_config.dot_texture_id         = qb_re_t_sprite_general;
    	text_config.dot_frame              = 2;
    	text_config.at_sprite_id           = qb_sp_alphabet_regular_special;
    	text_config.at_texture_id          = qb_re_t_sprite_general;
    	text_config.at_frame               = 5;
    	text_config.equal_sprite_id		   = qb_sp_alphabet_regular_special;
    	text_config.equal_texture_id       = qb_re_t_sprite_general;
    	text_config.equal_frame            = 6;
        factory::ui::create_text(text_config);

        text_config.name           = "row_2";
        text_config.local_position = {80, 256};
        text_config.text           = "all rights reserved";
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_3";
        text_config.local_position = {128, 320};
        text_config.text           = "coin  =   play";
        factory::ui::create_text(text_config);
        
        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr;
        number_config.name           = "number_1";
        number_config.local_position = {64, 240};
        number_config.number         = 1982;
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_number(number_config);
        
        number_config.name           = "number_2";
        number_config.local_position = {96, 320};
        number_config.number         = 1;
        factory::ui::create_number(number_config);
    	
        number_config.name           = "number_3";
        number_config.local_position = {256, 320};
        number_config.number         = 1;
        factory::ui::create_number(number_config);
    	
    	sprite_config.scene_ptr      = scene_ptr;
    	sprite_config.name           = "disk";
    	sprite_config.sprite_id      = qb_sp_level_1_disk_1;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
    	auto sprite_info = factory::ui::create_sprite(sprite_config);
    	auto disk_ptr = sprite_info.go_ptr;
        
    	sprite_config.name           = "qbert_right";
    	sprite_config.sprite_id      = qb_sp_qbert_player_1;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
    	sprite_config.curr_frame     = 5;
    	sprite_config.cached		 = false;
    	sprite_info = factory::ui::create_sprite(sprite_config);
    	sprite_info.go_ptr->set_parent(disk_ptr);
    	sprite_info.go_ptr->set_local_position(4.0f, -14.0f);
    }

    void scene_loader::load_menu_scene_2()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("menu_2");
        scene_ptr->set_active(false);
        
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "text_qbert";
        sprite_config.local_position = {38, 32};
        sprite_config.sprite_id      = qb_sp_text_qbert;
        factory::ui::create_sprite(sprite_config);

        factory::ui::text_config_info text_config{};
        text_config.scene_ptr              = scene_ptr;
        text_config.name                   = "row_1";
        text_config.local_position         = {96, 112};
        text_config.text                   = "jump on squares to";
    	text_config.sprite_id              = qb_sp_alphabet_regular_green;
    	text_config.texture_id             = qb_re_t_sprite_general;
    	text_config.space_sprite_id        = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id       = qb_re_t_sprite_general;
    	text_config.exclamation_sprite_id  = qb_sp_alphabet_regular_special;
    	text_config.exclamation_texture_id = qb_re_t_sprite_general;
    	text_config.exclamation_frame      = 3;
        auto text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "1"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_2";
        text_config.local_position = {96, 128};
        text_config.text           = "change them to";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "1"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_3";
        text_config.local_position = {96, 144};
        text_config.text           = "the target color";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "1"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_4";
        text_config.local_position = {112, 176};
        text_config.text           = "stay on playfield!";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "2"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_5";
        text_config.local_position = {112, 192};
        text_config.text           = "jumping off results";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "2"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_6";
        text_config.local_position = {112, 208};
        text_config.text           = "in a fatal plummet";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "2"});
    	text_info.go_ptr->set_active(false);

        text_config.name           = "row_7";
        text_config.local_position = {112, 224};
        text_config.text           = "unless a disk is there";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "2"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_8";
        text_config.local_position = {128, 256};
        text_config.text           = "avoid all objects";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "3"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_9";
        text_config.local_position = {128, 272};
        text_config.text           = "and creatures that";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "3"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_10";
        text_config.local_position = {128, 288};
        text_config.text           = "are not green";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "3"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_11";
        text_config.local_position = {144, 320};
        text_config.text           = "use spinning disks";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "4"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_12";
        text_config.local_position = {144, 336};
        text_config.text           = "to lure snake to";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "4"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_14";
        text_config.local_position = {144, 352};
        text_config.text           = "his death";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "4"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_15";
        text_config.local_position = {160, 384};
        text_config.text           = "extra life at";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "5"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_16";
        text_config.local_position = {255, 400};
        text_config.text           = "and each";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "5"});
    	text_info.go_ptr->set_active(false);
        
        text_config.name           = "row_17";
        text_config.local_position = {160, 416};
        text_config.text           = "additional";
        text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tags({"instruction", "5"});
    	text_info.go_ptr->set_active(false);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr;
        number_config.name           = "number_1";
        number_config.local_position = {176, 400};
        number_config.number         = 8000;
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
        auto number_info = factory::ui::create_number(number_config);
    	number_info.go_ptr->add_tags({"instruction", "5"});
    	number_info.go_ptr->set_active(false);
        
        number_config.name           = "number_2";
        number_config.local_position = {336, 416};
        number_config.number         = 14000;
        number_info = factory::ui::create_number(number_config);
    	number_info.go_ptr->add_tags({"instruction", "5"});
    	number_info.go_ptr->set_active(false);
    	
		factory::character::player_config_info player_config{};
		player_config.scene_ptr         = scene_ptr;
		player_config.name              = "qbert";
		player_config.sprite_id         = qb_sp_qbert_player_1;
		player_config.texture_id        = qb_re_t_sprite_general;
		player_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_left};
		player_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_right};
		player_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_up};
		player_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_down};
		auto player_info = factory::character::create_ai_player(player_config);
    	player_info.go_ptr->component<jump_component>()->set_jump_offset(18.0f, 62.0f);
    	player_info.go_ptr->add_tag("menu_2");

    	auto swearing_go_ptr = scene_ptr->create_game_object("swearing");
    	swearing_go_ptr->set_parent(player_info.go_ptr);
    	swearing_go_ptr->set_local_position(-24.0f, -50.0f);
        swearing_go_ptr->add_component<mngn::sprite_ui_component>(qb_sp_qbert_swearing, sprite_config.texture_id);
    	swearing_go_ptr->set_active(false);

    	sprite_config.scene_ptr      = scene_ptr;
    	sprite_config.name           = "red_ball";
    	sprite_config.sprite_id      = qb_sp_ball_red;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
		auto sprite_info = factory::ui::create_sprite(sprite_config);
    	sprite_info.go_ptr->add_tag("menu_2");
    	sprite_info.go_ptr->set_active(false);
    }

    void scene_loader::load_menu_scene_3()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("menu_3");
        scene_ptr->set_active(false);
    	
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "qbert";
        sprite_config.local_position = {208, 24};
        sprite_config.sprite_id      = qb_sp_qbert_big;
        factory::ui::create_sprite(sprite_config);
    	
        factory::ui::text_config_info text_config{};
        text_config.scene_ptr              = scene_ptr;
        text_config.name                   = "row_1";
        text_config.local_position         = {48, 112};
        text_config.text                   = "keyboard";
    	text_config.sprite_id              = qb_sp_alphabet_regular_purple;
    	text_config.texture_id             = qb_re_t_sprite_general;
    	text_config.space_sprite_id        = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id       = qb_re_t_sprite_general;
    	text_config.exclamation_sprite_id  = qb_sp_alphabet_regular_special;
    	text_config.exclamation_texture_id = qb_re_t_sprite_general;
    	text_config.exclamation_frame      = 3;
    	text_config.equal_sprite_id		   = qb_sp_alphabet_regular_special;
    	text_config.equal_texture_id       = qb_re_t_sprite_general;
    	text_config.equal_frame            = 6;
    	text_config.hyphen_sprite_id	   = qb_sp_alphabet_regular_special;
    	text_config.hyphen_texture_id      = qb_re_t_sprite_general;
    	text_config.hyphen_frame           = 7;
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_2";
    	text_config.sprite_id              = qb_sp_alphabet_regular_green;
        text_config.local_position = {48, 128};
        text_config.text           = "player      = arrows"; // 1
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_3";
        text_config.local_position = {48, 144};
        text_config.text           = "player      = wasd"; // 2
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_4";
        text_config.local_position = {48, 160};
        text_config.text           = "accept      = return";
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_5";
        text_config.local_position = {48, 176};
        text_config.text           = "insert coin = right shift";
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_6";
        text_config.local_position = {48, 192};
        text_config.text           = "mute        = m";
        factory::ui::create_text(text_config);
    	
        text_config.name           = "row_6";
        text_config.local_position = {48, 208};
        text_config.text           = "skip level  = f";
        factory::ui::create_text(text_config);

        text_config.name           = "row_7";
        text_config.local_position = {48, 240};
        text_config.text           = "controller";
    	text_config.sprite_id      = qb_sp_alphabet_regular_purple;
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_8";
        text_config.local_position = {48, 256};
        text_config.text           = "player      = d-pad"; // 1
    	text_config.sprite_id      = qb_sp_alphabet_regular_green;
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_9";
        text_config.local_position = {48, 272};
        text_config.text           = "player      = d-pad"; // 2
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_10";
        text_config.local_position = {48, 288};
        text_config.text           = "insert coin = x";
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_11";
        text_config.local_position = {48, 304};
        text_config.text           = "accept      = a";
        factory::ui::create_text(text_config);
        
        text_config.name           = "row_12";
        text_config.local_position = {48, 320};
        text_config.text           = "mute        = b";
        factory::ui::create_text(text_config);
    	
        text_config.name           = "row_12";
        text_config.local_position = {48, 336};
        text_config.text           = "skip level  = y";
        factory::ui::create_text(text_config);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr;
        number_config.name           = "keyboard_player_1";
        number_config.local_position = {160, 128};
        number_config.number         = 1;
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_number(number_config);
    	
        number_config.name           = "controller_player_1";
        number_config.local_position = {160, 256};
        factory::ui::create_number(number_config);
    	
        number_config.name           = "f1";
        number_config.local_position = {288, 208};
        factory::ui::create_number(number_config);
        
        number_config.sprite_id      = qb_sp_numbers_regular_purple;
        number_config.name           = "keyboard_player_2";
        number_config.local_position = {160, 144};
        number_config.number         = 2;
        factory::ui::create_number(number_config);
    	
        number_config.name           = "controller_player_2";
        number_config.local_position = {160, 272};
        factory::ui::create_number(number_config);
        
        text_config.name           = "row_14";
        text_config.local_position = {160, 384};
        text_config.text           = "adam knapecz";
        factory::ui::create_text(text_config);
    	
        text_config.name           = "row_14";
        text_config.local_position = {144, 416};
        text_config.text           = "kortrijk -";
        factory::ui::create_text(text_config);
    	
        text_config.name           = "row_14";
        text_config.local_position = {240, 400};
        text_config.text           = "dae";
    	text_config.sprite_id      = qb_sp_alphabet_regular_purple;
        factory::ui::create_text(text_config);
    	
        number_config.name           = "number_2";
        number_config.local_position = {320, 416};
    	number_config.sprite_id	     = qb_sp_numbers_bold_pink;
        number_config.number         = 2024;
        factory::ui::create_number(number_config);
    }

    void scene_loader::load_loading_scene()
    {
    	for (int i = 1; i <= level_config_manager::instance().level_count(); ++i)
    	{
    		scene_info scene_info{};
			auto const scene_ptr = mngn::scene_manager::instance().create_scene(std::to_string(i) + "_loading");
			auto const root_ptr = scene_ptr->create_game_object("root");
			scene_ptr->set_active(false);

    		scene_info.scene_ptr = scene_ptr;
    		scene_info.root_ptr  = root_ptr;
    		scene_info.level_id = i;
    		scene_info.level_config = level_config_manager::instance().level_config();
    		
    		create_loading_sprite(scene_info);
    		create_loading_cubes(scene_info);
    		create_loading_qbert(scene_info);
    	}
    }

    void scene_loader::load_single_scenes()
    {
    	load_scenes("single", [this](scene_info scene_info)
		{
			create_single_scene(scene_info);
		});
    }

    void scene_loader::load_coop_scenes()
    {
    	load_scenes("coop", [this](scene_info scene_info)
		{
			create_coop_scene(scene_info);
		});
    }

    void scene_loader::load_versus_scenes()
    {
    	load_scenes("versus", [this](scene_info scene_info)
		{
			create_versus_scene(scene_info);
		});
    }

    void scene_loader::load_game_over_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("game_over");
        scene_ptr->set_active(false);

    	std::vector<mngn::sprite*> sprites;
    	std::generate_n(std::back_inserter(sprites), 9, []
    	{
    		return mngn::sprite_manager::instance().load_sprite(qb_sp_black_square, qb_re_t_sprite_general);
    	});
    	factory::ui::multisprite_config_info multisprite_config{};
    	multisprite_config.scene_ptr      = scene_ptr;
    	multisprite_config.name           = "game_over";
    	multisprite_config.local_position = {176.0f, 288.0f};
    	multisprite_config.sprites		  = sprites;
    	factory::ui::create_multisprite(multisprite_config);
    	
		factory::ui::text_config_info text_config{};
		text_config.scene_ptr        = scene_ptr;
		text_config.name             = "text_game_over";
		text_config.local_position   = {176.0f, 288.0f};
		text_config.sprite_id        = qb_sp_alphabet_regular_purple;
		text_config.texture_id       = qb_re_t_sprite_general;
		text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
		text_config.space_texture_id = qb_re_t_sprite_general;
		text_config.text             = "game over";
		factory::ui::create_flickering_text(text_config);
    }

    void scene_loader::load_input_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("input");
        scene_ptr->set_active(false);

    	factory::ui::text_config_info text_config{};
    	text_config.scene_ptr        = scene_ptr;
    	text_config.local_position   = {142.0f, 92.0f};
    	text_config.sprite_id        = qb_sp_alphabet_regular_purple;
    	text_config.texture_id       = qb_re_t_sprite_general;

    	glm::vec2 start_pos {64.0f, 288.0f};
        constexpr float offset_x = 64.0f;
        constexpr float offset_y = 32.0f;
    	bool indented  = false;

    	for (int i = 1, c = 'a'; i <= 26; ++i, ++c)
    	{
    		text_config.local_position.x = start_pos.x + offset_x * ((i - 1) % 6);
    		text_config.local_position.y = start_pos.y;
    		text_config.name             = std::string{"text_"} + static_cast<char>(c);
    		text_config.text             = static_cast<char>(c);
    		auto text_info = factory::ui::create_text(text_config);
    		text_info.go_ptr->add_tag(std::to_string(i - 1));
    		
    		if (i % 6 == 0)
    		{
    			if (indented)
    			{
    				indented = false;
    				start_pos.x -= offset_y;
    			}
    			else
    			{
    				indented = true;
    				start_pos.x += offset_y;
    			}
    			start_pos.y += offset_y;
    		}
    	}

    	text_config.local_position = {80.0f, 464.0f};
    	text_config.name = "text_time";
    	text_config.text = "time";
    	factory::ui::create_text(text_config);
    	
		factory::ui::sprite_config_info sprite_config{};
		sprite_config.scene_ptr      = scene_ptr;
		sprite_config.name           = "text_rub";
		sprite_config.local_position = {320.0f, 416.0f};
		sprite_config.sprite_id      = qb_sp_text_rub;
		sprite_config.texture_id     = qb_re_t_sprite_general;
		auto sprite_info = factory::ui::create_sprite(sprite_config);
		sprite_info.go_ptr->add_tag(std::to_string(28));
		
		sprite_config.name           = "text_end";
		sprite_config.local_position = {384.0f, 416.0f};
		sprite_config.sprite_id      = qb_sp_text_end;
		sprite_info = factory::ui::create_sprite(sprite_config);
		sprite_info.go_ptr->add_tag(std::to_string(29));
    	
    	sprite_config.name           = "dot";
    	sprite_config.local_position = {256.0f, 416.0f};
    	sprite_config.sprite_id	  = qb_sp_alphabet_regular_special;
    	sprite_config.curr_frame     = 16;
    	sprite_config.cached         = false;
    	sprite_info = factory::ui::create_sprite(sprite_config);
		sprite_info.go_ptr->add_tag(std::to_string(27));
    	
    	sprite_config.name           = "space";
    	sprite_config.local_position = {192.0f, 416.0f};
    	sprite_config.sprite_id	  = qb_sp_alphabet_regular_space;
    	sprite_info = factory::ui::create_sprite(sprite_config);
		sprite_info.go_ptr->add_tag(std::to_string(26));
    	
    	sprite_config.name           = "underline";
    	sprite_config.local_position = {64.0f, 304.0f};
    	sprite_config.sprite_id	  = qb_sp_alphabet_regular_special;
    	sprite_config.curr_frame     = 11;
    	sprite_config.cached         = false;
    	sprite_info = factory::ui::create_sprite(sprite_config);
    	sprite_info.go_ptr->add_component<flicker_component>();
    	sprite_info.go_ptr->add_tag("active");
    }

    void scene_loader::load_scoreboard_scene()
    {
	    auto scene_ptr = mngn::scene_manager::instance().create_scene("scoreboard");
    	scene_ptr->set_active(false);

    	factory::ui::sprite_config_info sprite_config{};
    	sprite_config.scene_ptr      = scene_ptr;
    	sprite_config.name           = "qbert_left";
    	sprite_config.local_position = {108.0f, 42.0f};
    	sprite_config.sprite_id      = qb_sp_qbert_player_1;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
    	sprite_config.curr_frame     = 7;
    	sprite_config.cached         = false;
    	factory::ui::create_sprite(sprite_config);
    	
    	sprite_config.name           = "qbert_right";
    	sprite_config.local_position = {354.0f, 42.0f};
    	sprite_config.curr_frame     = 5;
    	factory::ui::create_sprite(sprite_config);

    	factory::ui::text_config_info text_config{};
    	text_config.scene_ptr        = scene_ptr;
    	text_config.name             = "text_high_scores";
    	text_config.local_position   = {160.0f, 48.0f};
    	text_config.sprite_id        = qb_sp_alphabet_regular_purple;
    	text_config.texture_id       = qb_re_t_sprite_general;
    	text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id = qb_re_t_sprite_general;
    	text_config.text             = "high scores";
    	factory::ui::create_text(text_config);

    	std::vector<mngn::sprite*> sprites;
    	std::generate_n(std::back_inserter(sprites), 4, []
    	{
    		auto const sprite_ptr  = mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general, false);
    		sprite_ptr->set_current_frame(11);
    		return sprite_ptr;
    	});

    	factory::ui::multisprite_config_info multisprite_config{};
    	multisprite_config.scene_ptr      = scene_ptr;
    	multisprite_config.name           = "underline_1";
    	multisprite_config.local_position = {160.0f, 64.0f};
    	multisprite_config.sprites		  = sprites;
    	factory::ui::create_multisprite(multisprite_config);

    	std::generate_n(std::back_inserter(sprites), 2, []
    	{
    		auto const sprite_ptr  = mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general, false);
    		sprite_ptr->set_current_frame(11);
    		return sprite_ptr;
    	});
    	multisprite_config.scene_ptr      = scene_ptr;
    	multisprite_config.name           = "underline_2";
    	multisprite_config.local_position = {240.0f, 64.0f};
    	multisprite_config.sprites		  = sprites;
    	factory::ui::create_multisprite(multisprite_config);

    	factory::ui::number_config_info number_config{};
    	number_config.scene_ptr      = scene_ptr;
    	number_config.name           = "rank_number";
    	number_config.sprite_id      = qb_sp_numbers_regular_orange;
    	number_config.texture_id     = qb_re_t_sprite_general;

		sprite_config.name = "red_parenthesis";
    	sprite_config.sprite_id = qb_sp_alphabet_regular_special;
    	sprite_config.curr_frame = 21;

	    constexpr glm::vec2 start_pos{16.0f, 144.0f};
	    constexpr float offset_x = 224.0f;
	    constexpr float offset_y = 32.0f;

    	for (int i = 0, j = 2; i < 22; ++i, ++j)
    	{
    		number_config.number = j;
    		bool const is_even = i % 2 == 0;
    		bool const is_single_digit = j < 10;

    		float const x_base = start_pos.x + (is_even ? 0 : offset_x);
    		float const y_base = start_pos.y + (i / 2) * offset_y;
    		float const x_offset = is_single_digit ? offset_y / 2 : 0;
			
    		number_config.local_position = {x_base + x_offset, y_base};
    		sprite_config.local_position = {number_config.local_position.x + (is_single_digit ? offset_y / 2 : offset_y), y_base};
    		factory::ui::create_sprite(sprite_config);
    		factory::ui::create_number(number_config);
    	}
    }

    void scene_loader::create_single_scene(scene_info &scene_info)
    {
    	create_ui(scene_info);
    	create_bonus(scene_info);
    	create_score_display(scene_info);
    	create_health_display(scene_info);
    	create_level_display(scene_info);
    	create_round_display(scene_info);
    	create_level(scene_info);
    	create_player_1(scene_info);
    	bind_player_observers(scene_info);

    	create_npcs(scene_info);
    }

    void scene_loader::create_coop_scene(scene_info &scene_info)
    {
    	create_ui(scene_info);
    	create_bonus(scene_info);
    	create_score_display(scene_info);
    	create_health_display(scene_info);
    	create_level_display(scene_info);
    	create_round_display(scene_info);
    	create_level(scene_info);
    	create_player_1(scene_info, true);
    	bind_player_observers(scene_info);
    	
    	create_npcs(scene_info);

        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_info.scene_ptr;
    	sprite_config.parent_ptr     = scene_info.root_ptr;
        sprite_config.name           = scene_info.scene_id + "text_player_2";
        sprite_config.local_position = {332, 32};
        sprite_config.sprite_id      = qb_sp_text_orange_player;
        sprite_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_2";
        sprite_config.local_position = {444, 16};
        sprite_config.sprite_id      = qb_sp_text_two;
        factory::ui::create_sprite(sprite_config);

		factory::ui::health_display_config_info health_display_config{};
		health_display_config.scene_ptr      = scene_info.scene_ptr;
		health_display_config.parent_ptr     = scene_info.root_ptr;
		health_display_config.name           = scene_info.scene_id + "health_2";
		health_display_config.local_position = {448.0f, 160.0f};
		scene_info.health_display_info = factory::ui::create_health_display(health_display_config);
    	
    	create_player_2(scene_info);
    	bind_player_observers(scene_info);
    }

    void scene_loader::create_versus_scene(scene_info &scene_info)
    {
    	create_ui(scene_info);
    	create_bonus(scene_info);
    	create_score_display(scene_info);
    	create_health_display(scene_info);
    	create_level_display(scene_info);
    	create_round_display(scene_info);
    	create_level(scene_info);
    	create_player_1(scene_info);
    	bind_player_observers(scene_info);
    	
    	create_npcs(scene_info);
    }

    void scene_loader::create_score_display(scene_info &scene_info)
    {
		factory::ui::score_display_config_info score_display_config{};
		score_display_config.scene_ptr      = scene_info.scene_ptr;
		score_display_config.parent_ptr     = scene_info.root_ptr;
		score_display_config.name           = scene_info.scene_id + "score_1";
		score_display_config.local_position = {32.0f,    48.0f};
		score_display_config.sprite_id	    = qb_sp_numbers_regular_orange;
		score_display_config.texture_id     = qb_re_t_sprite_general;
		scene_info.score_display_info = factory::ui::create_score_display(score_display_config);
    }

    void scene_loader::create_health_display(scene_info &scene_info)
    {
		factory::ui::health_display_config_info health_display_config{};
		health_display_config.scene_ptr      = scene_info.scene_ptr;
		health_display_config.parent_ptr     = scene_info.root_ptr;
		health_display_config.name           = scene_info.scene_id + "health_1";
		health_display_config.local_position = {16.0f, 160.0f};
		scene_info.health_display_info = factory::ui::create_health_display(health_display_config);
    }

    void scene_loader::create_level_display(scene_info &scene_info)
    {
		factory::ui::level_display_config_info level_display_config{};
		level_display_config.scene_ptr      = scene_info.scene_ptr;
		level_display_config.parent_ptr     = scene_info.root_ptr;
		level_display_config.name           = scene_info.scene_id + "numbers_level";
		level_display_config.local_position = {432.0f, 80.0f};
		level_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		level_display_config.texture_id     = qb_re_t_sprite_general;
		scene_info.level_display_info = factory::ui::create_level_display(level_display_config);
    }

    void scene_loader::create_round_display(scene_info &scene_info)
    {
		factory::ui::round_display_config_info round_display_config{};
		round_display_config.scene_ptr      = scene_info.scene_ptr;
		round_display_config.parent_ptr     = scene_info.root_ptr;
		round_display_config.name           = scene_info.scene_id + "round";
		round_display_config.local_position = {432.0f, 96.0f};
		round_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		round_display_config.texture_id     = qb_re_t_sprite_general;
		scene_info.round_display_info = factory::ui::create_round_display(round_display_config);
    }

    void scene_loader::create_level(scene_info &scene_info)
    {
	    factory::level::level_config_info config{};
    	config.scene_ptr    = scene_info.scene_ptr;
    	config.parent_ptr   = scene_info.root_ptr;
    	config.scene_id	 = scene_info.scene_id;
    	config.cube_color_1 = scene_info.level_config["cube_color_1"];
    	config.cube_color_2 = scene_info.level_config["cube_color_2"];
    	if (scene_info.level_config.contains("cube_color_3")) config.cube_color_3 = scene_info.level_config["cube_color_3"];
    	if (scene_info.level_config.contains("cube_revertible")) config.cube_revertible = scene_info.level_config["cube_revertible"];
    	config.cube_color_small    = scene_info.level_config["cube_color_small"];
    	config.cube_animated	   = scene_info.level_config["cube_animated"];
    	config.cube_animated_small = scene_info.level_config["cube_animated_small"];
    	config.disk_count          = scene_info.level_config["disk_count"];
    	config.disk_color          = scene_info.level_config["disk_color"];
    	config.disk_positions      = scene_info.level_config["disk_positions"];
        scene_info.level_info = factory::level::create_level(config);
    }

    void scene_loader::create_player_1(scene_info &scene_info, bool coop)
    {
		factory::character::player_config_info player_config{};
		player_config.scene_ptr         = scene_info.scene_ptr;
		player_config.parent_ptr        = scene_info.root_ptr;
		player_config.name              = "player_1";
		player_config.local_position    = coop ? glm::vec2{416.0f, 372.0f} : glm::vec2{224.0f, 84.0f};
		player_config.sprite_id         = qb_sp_qbert_player_1;
		player_config.texture_id        = qb_re_t_sprite_general;
		player_config.row_idx           = coop ? 6 : 0;
		player_config.col_idx           = coop ? 6 : 0;
		player_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_left};
		player_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_right};
		player_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_up};
		player_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_down};
		player_config.left_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_left, 0};
		player_config.right_command_alt = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_right, 0};
		player_config.up_command_alt    = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_up, 0};
		player_config.down_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_down, 0};
		scene_info.player_info = factory::character::create_player(player_config);
    }

    void scene_loader::create_player_2(scene_info &scene_info)
    {
		factory::character::player_config_info player_config{};
		player_config.scene_ptr      = scene_info.scene_ptr;
		player_config.parent_ptr     = scene_info.root_ptr;
		player_config.name           = "player_2";
		player_config.local_position = {32.0f, 372.0f};
		player_config.sprite_id      = qb_sp_qbert_player_2;
		player_config.texture_id     = qb_re_t_sprite_general;
		player_config.row_idx        = 6;
		player_config.col_idx        = 0;
		player_config.left_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_a};
		player_config.right_command  = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_d};
		player_config.up_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_w};
		player_config.down_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_s};
		player_config.left_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_left, 1};
		player_config.right_command_alt = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_right, 1};
		player_config.up_command_alt    = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_up, 1};
		player_config.down_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_down, 1};
		scene_info.player_info = factory::character::create_player(player_config);
    }

    void scene_loader::bind_player_observers(scene_info &scene_info)
    {
		mngn::collision_manager::instance().register_collider(scene_info.player_info.collider_comp_ptr);
		scene_info.player_info.health_comp_ptr->add_observer(scene_info.health_display_info.health_display_comp_ptr);
		scene_info.player_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.player_info.score_counter_comp_ptr->add_observer(scene_info.score_display_info.score_display_comp_ptr);
		scene_info.player_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.player_info.level_counter_comp_ptr->add_observer(scene_info.level_display_info.level_display_comp_ptr);
		scene_info.player_info.round_counter_comp_ptr->add_observer(scene_info.round_display_info.round_display_comp_ptr);
    	scene_info.player_info.collider_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		std::ranges::for_each(scene_info.level_info.cube_info.cube_components, [scene_info](auto cube_comp_ptr) { scene_info.player_info.position_comp_ptr->add_observer(cube_comp_ptr); });
		std::ranges::for_each(scene_info.level_info.cube_info.cube_components, [scene_info](auto cube_comp_ptr) { cube_comp_ptr->add_observer(scene_info.level_manager_comp_ptr); });
    }

    void scene_loader::bind_generic_commands()
    {
    	auto game_state_comp_ptr = scene_utility::instance().game_state();
    	
    	// Game mode selection (single, coop, versus)
	    auto left_game_state_cmd = std::make_unique<game_mode_select_command>(game_state_comp_ptr, -1);
	    auto right_game_state_cmd = std::make_unique<game_mode_select_command>(game_state_comp_ptr, 1);

    	mngn::input_config_info key_config{};
    	key_config.input_type  = mngn::input_type::keyboard;
    	key_config.input_state = mngn::input_state::down;

    	mngn::input_config_info controller_config{};
    	controller_config.input_type  = mngn::input_type::controller;
    	controller_config.input_state = mngn::input_state::down;

    	key_config.input = mngn::input::k_left;
		mngn::input_manager::instance().bind_command(key_config, left_game_state_cmd->clone());
    	key_config.input = mngn::input::k_a;
		mngn::input_manager::instance().bind_command(key_config, left_game_state_cmd->clone());
    	key_config.input = mngn::input::k_right;
		mngn::input_manager::instance().bind_command(key_config, right_game_state_cmd->clone());
    	key_config.input = mngn::input::k_d;
		mngn::input_manager::instance().bind_command(key_config, right_game_state_cmd->clone());
    	
    	controller_config.input = mngn::input::c_left;
    	controller_config.controller_idx = 0;
		mngn::input_manager::instance().bind_command(controller_config, left_game_state_cmd->clone());
    	controller_config.controller_idx = 1;
		mngn::input_manager::instance().bind_command(controller_config, std::move(left_game_state_cmd));
    	controller_config.input = mngn::input::c_right;
    	controller_config.controller_idx = 0;
		mngn::input_manager::instance().bind_command(controller_config, right_game_state_cmd->clone());
    	controller_config.controller_idx = 1;
		mngn::input_manager::instance().bind_command(controller_config, std::move(right_game_state_cmd));

    	// Game mode accept
    	auto game_state_cmd = std::make_unique<game_mode_accept_command>(game_state_comp_ptr);
    	key_config.input = mngn::input::k_return;
    	mngn::input_manager::instance().bind_command(key_config, game_state_cmd->clone());
    	controller_config.input = mngn::input::c_a;
    	controller_config.controller_idx = 0;
    	mngn::input_manager::instance().bind_command(controller_config, game_state_cmd->clone());
    	controller_config.controller_idx = 1;
    	mngn::input_manager::instance().bind_command(controller_config, std::move(game_state_cmd));

    	// Select characters for the initials
    	auto left_input_cmd = std::make_unique<input_select_command>(game_state_comp_ptr, -1);
    	auto right_input_cmd = std::make_unique<input_select_command>(game_state_comp_ptr, 1);

    	key_config.input = mngn::input::k_left;
    	mngn::input_manager::instance().bind_command(key_config, left_input_cmd->clone());
    	key_config.input = mngn::input::k_a;
    	mngn::input_manager::instance().bind_command(key_config, left_input_cmd->clone());
    	key_config.input = mngn::input::k_right;
    	mngn::input_manager::instance().bind_command(key_config, right_input_cmd->clone());
    	key_config.input = mngn::input::k_d;
    	mngn::input_manager::instance().bind_command(key_config, right_input_cmd->clone());

    	controller_config.input = mngn::input::c_left;
    	controller_config.controller_idx = 0;
    	mngn::input_manager::instance().bind_command(controller_config, left_input_cmd->clone());
    	controller_config.controller_idx = 1;
    	mngn::input_manager::instance().bind_command(controller_config, std::move(left_input_cmd));
    	controller_config.input = mngn::input::c_right;
    	controller_config.controller_idx = 0;
    	mngn::input_manager::instance().bind_command(controller_config, right_input_cmd->clone());
    	controller_config.controller_idx = 1;
    	mngn::input_manager::instance().bind_command(controller_config, std::move(right_input_cmd));

    	// Accept characters for the initials
    	auto input_accept_cmd = std::make_unique<input_accept_command>(game_state_comp_ptr);
    	key_config.input = mngn::input::k_return;
    	mngn::input_manager::instance().bind_command(key_config, input_accept_cmd->clone());
    	controller_config.input = mngn::input::c_a;
    	controller_config.controller_idx = 0;
		mngn::input_manager::instance().bind_command(controller_config, input_accept_cmd->clone());
    	controller_config.controller_idx = 1;
		mngn::input_manager::instance().bind_command(controller_config, std::move(input_accept_cmd));

    	// Mute
    	auto toggle_mute_cmd = std::make_unique<toggle_mute_command>();
    	key_config.input = mngn::input::k_m;
    	mngn::input_manager::instance().bind_command(key_config, toggle_mute_cmd->clone());
    	controller_config.input = mngn::input::c_b;
    	controller_config.controller_idx = 0;
    	mngn::input_manager::instance().bind_command(controller_config, toggle_mute_cmd->clone());
    	controller_config.controller_idx = 1;
    	mngn::input_manager::instance().bind_command(controller_config, std::move(toggle_mute_cmd));

    	// Skip level
    	auto skip_level_cmd = std::make_unique<skip_round_command>();
    	key_config.input = mngn::input::k_f1;
    	mngn::input_manager::instance().bind_command(key_config, skip_level_cmd->clone());
    	controller_config.input = mngn::input::c_y;
    	controller_config.controller_idx = 0;
    	mngn::input_manager::instance().bind_command(controller_config, skip_level_cmd->clone());
    	controller_config.controller_idx = 1;
    	mngn::input_manager::instance().bind_command(controller_config, std::move(skip_level_cmd));

    	// Insert coin
    	auto insert_coind_cmd = std::make_unique<insert_coin_command>();
    	key_config.input = mngn::input::k_right_shift;
    	mngn::input_manager::instance().bind_command(key_config, insert_coind_cmd->clone());
		controller_config.input = mngn::input::c_x;
    	controller_config.controller_idx = 0;
		mngn::input_manager::instance().bind_command(controller_config, insert_coind_cmd->clone());
    	controller_config.controller_idx = 1;
		mngn::input_manager::instance().bind_command(controller_config, std::move(insert_coind_cmd));
    }

    void scene_loader::create_red_ball(scene_info &scene_info)
    {
		factory::character::red_ball_config_info red_ball_config{};
		red_ball_config.scene_ptr      = scene_info.scene_ptr;
		red_ball_config.parent_ptr     = scene_info.root_ptr;
		red_ball_config.name           = scene_info.scene_id + "red_ball_" + scene_info.npc_config_info.name;
    	red_ball_config.local_position = {-32.0f, -32.0f};
		red_ball_config.sprite_id	   = qb_sp_ball_red;
		red_ball_config.texture_id     = qb_re_t_sprite_general;
    	red_ball_config.spawn_time_min = scene_info.npc_config_info.spawn_time_min;
    	red_ball_config.spawn_time_max   = scene_info.npc_config_info.spawn_time_max;
		scene_info.red_ball_info = factory::character::create_red_ball(red_ball_config);
    	
		// Observers
		scene_info.red_ball_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.red_ball_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
    }

    void scene_loader::create_npcs(scene_info &scene_info)
    {
    	auto npcs = scene_info.level_config["npcs"];

    	for (auto const &npc : npcs)
    	{
		    std::string const name = npc["name"];
    		scene_info.npc_config_info.spawn_time_min = npc["spawn_time_min"];
    		scene_info.npc_config_info.spawn_time_max   = npc["spawn_time_max"];
    		int const count = npc["count"];

    		if (name == "red_ball")
    		{
    			for (int i = 0; i < count; ++i)
				{
    				scene_info.npc_config_info.name = std::to_string(i + 1);
					create_red_ball(scene_info);
				}
    		}
    		else if (name == "coily")
    		{
    			for (int i = 0; i < count; ++i)
    			{
    				scene_info.npc_config_info.name = std::to_string(i + 1);
    				create_coily(scene_info);
    			}
    		}
    		else if (name == "ugg")
			{
				for (int i = 0; i < count; ++i)
				{
					scene_info.npc_config_info.name = std::to_string(i + 1);
					create_ugg(scene_info);
				}
			}
			else if (name == "wrong_way")
			{
				for (int i = 0; i < count; ++i)
				{
					scene_info.npc_config_info.name = std::to_string(i + 1);
					create_wrong_way(scene_info);
				}
			}
			else if (name == "green_ball")
			{
				for (int i = 0; i < count; ++i)
				{
					scene_info.npc_config_info.name = std::to_string(i + 1);
					create_green_ball(scene_info);
				}
			}
			else if (name == "slick")
			{
				for (int i = 0; i < count; ++i)
				{
					scene_info.npc_config_info.name = std::to_string(i + 1);
					create_slick(scene_info);
				}
			}
			else if (name == "sam")
			{
				for (int i = 0; i < count; ++i)
				{
					scene_info.npc_config_info.name = std::to_string(i + 1);
					create_sam(scene_info);
				}
			}
	    }
    }

    void scene_loader::create_coily(scene_info &scene_info)
    {
		factory::character::coily_config_info coily_config{};
		coily_config.scene_ptr      = scene_info.scene_ptr;
		coily_config.parent_ptr     = scene_info.root_ptr;
		coily_config.name           = scene_info.scene_id + "coily_" + scene_info.npc_config_info.name;
    	coily_config.local_position = {-32.0f, -32.0f};
		coily_config.sprite_id	    = qb_sp_coily_egg;
		coily_config.texture_id     = qb_re_t_sprite_general;
		coily_config.left_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_a};
		coily_config.right_command  = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_d};
		coily_config.up_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_w};
		coily_config.down_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_s};
		coily_config.left_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_left, 1};
		coily_config.right_command_alt = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_right, 1};
		coily_config.up_command_alt    = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_up, 1};
		coily_config.down_command_alt  = {mngn::input_type::controller, mngn::input_state::down, mngn::input::c_down, 1};
		scene_info.coily_info = factory::character::create_coily(coily_config);
    	
		// Observers
		scene_info.coily_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.coily_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
    }

    void scene_loader::create_ugg(scene_info &scene_info)
    {
		factory::character::ugg_config_info ugg_config{};
		ugg_config.scene_ptr      = scene_info.scene_ptr;
		ugg_config.parent_ptr     = scene_info.root_ptr;
		ugg_config.name           = scene_info.scene_id + "ugg_" + scene_info.npc_config_info.name;
    	ugg_config.local_position = {-32.0f, -32.0f};
		ugg_config.sprite_id	  = qb_sp_ugg;
		ugg_config.texture_id     = qb_re_t_sprite_general;
		auto ugg_info = factory::character::create_ugg(ugg_config);
    	
		// Observers
		ugg_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		ugg_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
    }

    void scene_loader::create_wrong_way(scene_info &scene_info)
    {
		factory::character::wrong_way_config_info wrong_way_config{};
		wrong_way_config.scene_ptr      = scene_info.scene_ptr;
		wrong_way_config.parent_ptr     = scene_info.root_ptr;
		wrong_way_config.name           = scene_info.scene_id + "wrong_way_" + scene_info.npc_config_info.name;
    	wrong_way_config.local_position = {-32.0f, -32.0f};
		wrong_way_config.sprite_id	    = qb_sp_wrong_way;
		wrong_way_config.texture_id     = qb_re_t_sprite_general;
		scene_info.wrong_way_info = factory::character::create_wrong_way(wrong_way_config);
    	
		// Observers
		scene_info.wrong_way_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.wrong_way_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
    }

    void scene_loader::create_green_ball(scene_info &scene_info)
    {
		factory::character::green_ball_config_info green_ball_config{};
		green_ball_config.scene_ptr      = scene_info.scene_ptr;
		green_ball_config.parent_ptr     = scene_info.root_ptr;
		green_ball_config.name           = scene_info.scene_id + "green_ball_" + scene_info.npc_config_info.name;
    	green_ball_config.local_position = {-32.0f, -32.0f};
		green_ball_config.sprite_id      = qb_sp_ball_green;
		green_ball_config.texture_id     = qb_re_t_sprite_general;
		scene_info.green_ball_info = factory::character::create_green_ball(green_ball_config);
    	
		// Observers
		scene_info.green_ball_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.green_ball_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
    }

    void scene_loader::create_slick(scene_info &scene_info)
    {
		factory::character::slick_config_info slick_config{};
		slick_config.scene_ptr      = scene_info.scene_ptr;
		slick_config.parent_ptr     = scene_info.root_ptr;
		slick_config.name           = scene_info.scene_id + "slick_" + scene_info.npc_config_info.name;
    	slick_config.local_position = {-32.0f, -32.0f};
		slick_config.sprite_id      = qb_sp_slick;
		slick_config.texture_id     = qb_re_t_sprite_general;
		scene_info.slick_info = factory::character::create_slick(slick_config);
    	
		// Observers
		scene_info.slick_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.slick_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		std::ranges::for_each(scene_info.level_info.cube_info.cube_components, [scene_info](auto cube_comp_ptr) { scene_info.slick_info.position_comp_ptr->add_observer(cube_comp_ptr); });
    }

    void scene_loader::create_sam(scene_info &scene_info)
    {
		factory::character::sam_config_info sam_config{};
		sam_config.scene_ptr      = scene_info.scene_ptr;
		sam_config.parent_ptr     = scene_info.root_ptr;
		sam_config.name           = scene_info.scene_id + "sam_" + scene_info.npc_config_info.name;
    	sam_config.local_position = {-32.0f, -32.0f};
		sam_config.sprite_id      = qb_sp_sam;
		sam_config.texture_id     = qb_re_t_sprite_general;
		scene_info.sam_info       = factory::character::create_sam(sam_config);
		// Observers
		scene_info.sam_info.position_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		scene_info.sam_info.health_comp_ptr->add_observer(scene_info.level_manager_comp_ptr);
		std::ranges::for_each(scene_info.level_info.cube_info.cube_components, [scene_info](auto cube_comp_ptr) { scene_info.sam_info.position_comp_ptr->add_observer(cube_comp_ptr); });
    }

    void scene_loader::create_ui(scene_info &scene_info)
    {
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_info.scene_ptr;
    	sprite_config.parent_ptr     = scene_info.root_ptr;
        sprite_config.name           = scene_info.scene_id + "text_player_1";
        sprite_config.local_position = {32, 32};
        sprite_config.sprite_id      = qb_sp_text_purple_player;
        sprite_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = scene_info.scene_id + "text_1";
        sprite_config.local_position = {144, 16};
        sprite_config.sprite_id      = qb_sp_text_one;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name = scene_info.scene_id + "text_change_to";
        sprite_config.local_position = {32, 80};
        sprite_config.sprite_id      = qb_sp_text_change_to;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name = scene_info.scene_id + "text_level";
        sprite_config.local_position = {368, 80};
        sprite_config.sprite_id      = qb_sp_text_level;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = scene_info.scene_id + "text_round";
        sprite_config.local_position = {368, 96};
        sprite_config.sprite_id      = qb_sp_text_round;
        factory::ui::create_sprite(sprite_config);
        
        factory::ui::arrow_config_info arrow_config{};
        arrow_config.scene_ptr      = scene_info.scene_ptr;
    	arrow_config.parent_ptr	    = scene_info.root_ptr;
        arrow_config.name           = scene_info.scene_id + "left_arrow_1";
        arrow_config.local_position = {32, 96};
        arrow_config.sprite_id      = qb_sp_arrow_right;
        arrow_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = scene_info.scene_id + "left_arrow_2";
        arrow_config.local_position = {48, 96};
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);    
        
        arrow_config.name           = scene_info.scene_id + "right_arrow_1";
        arrow_config.local_position = {96, 96};
        arrow_config.sprite_id      = qb_sp_arrow_left;
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = scene_info.scene_id + "right_arrow_2";
        arrow_config.local_position = {112, 96};
        arrow_config.delay          = 0.0f;
        factory::ui::create_arrow(arrow_config);
    }

    void scene_loader::create_bonus(scene_info &scene_info)
    {
	    factory::ui::text_config_info text_config{};
    	text_config.scene_ptr        = scene_info.scene_ptr;
    	text_config.parent_ptr       = scene_info.root_ptr;
    	text_config.name             = scene_info.scene_id + "text_bonus";
    	text_config.local_position   = {144.0f, 464.0f};
    	text_config.sprite_id        = qb_sp_alphabet_regular_purple;
    	text_config.texture_id       = qb_re_t_sprite_general;
    	text_config.text			 = "bonus";
    	auto text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->set_active(false);
    	text_info.go_ptr->add_tags({"ui", "bonus"});

    	factory::ui::number_config_info number_config{};
    	number_config.scene_ptr      = scene_info.scene_ptr;
    	number_config.parent_ptr     = scene_info.root_ptr;
    	number_config.name           = scene_info.scene_id + "number_bonus";
    	number_config.local_position = {256.0f, 464.0f};
    	number_config.sprite_id      = qb_sp_numbers_regular_orange;
    	number_config.texture_id     = qb_re_t_sprite_general;
    	number_config.number		 = scene_info.bonus;
    	auto number_info = factory::ui::create_number(number_config);
    	number_info.go_ptr->set_active(false);
    	number_info.go_ptr->add_tags({"ui", "bonus", "bonus_number"});
    }

    void scene_loader::create_loading_cubes(scene_info &scene_info)
    {
        for (auto const &level_config : scene_info.level_config["levels"])
        {
            if (level_config["level_id"] == scene_info.level_id)
            {
                factory::level::cube_config_info cube_config{};
                cube_config.scene_ptr      = scene_info.scene_ptr;
            	cube_config.parent_ptr     = scene_info.root_ptr;
                cube_config.name           = "cube_1";
                cube_config.local_position = {208.0f, 80.0f};
                cube_config.texture_id     = qb_re_t_sprite_general;
                cube_config.color_1        = level_config["cube_color_1"];
                cube_config.color_2        = level_config["cube_color_2"];
                if (level_config.contains("cube_color_3")) cube_config.color_3 = level_config["cube_color_3"];
                if (level_config.contains("cube_revertible")) cube_config.revertible = level_config["cube_revertible"];
                cube_config.row_idx = 0;
                cube_config.col_idx = 0;
                auto cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
            	scene_info.level_info.cube_info.cube_components.push_back(cube_info.go_ptr->component<cube_component>());
                
                cube_config.name           = "cube_2";
                cube_config.local_position = {176.0f, 128.0f};
                cube_config.row_idx        = 1;
                cube_config.col_idx        = 0;
                cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
            	scene_info.level_info.cube_info.cube_components.push_back(cube_info.go_ptr->component<cube_component>());
                
                cube_config.name           = "cube_3";
                cube_config.local_position = {240.0f, 128.0f};
                cube_config.row_idx        = 1;
                cube_config.col_idx        = 1;
                cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
            	scene_info.level_info.cube_info.cube_components.push_back(cube_info.go_ptr->component<cube_component>());
                
                cube_config.name           = "cube_4";
                cube_config.local_position = {208.0f, 176.0f};
                cube_config.row_idx        = 2;
                cube_config.col_idx        = 1;
                cube_info                  = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
            	scene_info.level_info.cube_info.cube_components.push_back(cube_info.go_ptr->component<cube_component>());

            	break;
            }
        }
    }

    void scene_loader::create_loading_sprite(scene_info &scene_info)
    {
		factory::ui::sprite_config_info sprite_config{};
    	sprite_config.scene_ptr      = scene_info.scene_ptr;
    	sprite_config.parent_ptr     = scene_info.root_ptr;
    	sprite_config.name           = "level";
    	sprite_config.local_position = {48.0f, 288.0f};
    	sprite_config.sprite_id      = scene_info.level_id + 10000;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
    	factory::ui::create_sprite(sprite_config);

        sprite_config.name = "green_circle";
        sprite_config.local_position = {208.0f, 400.0f};
        sprite_config.sprite_id = qb_sp_green_cirlce;
        factory::ui::create_sprite(sprite_config);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_info.scene_ptr;
        number_config.name           = "level_number";
        number_config.local_position = {226.0f, 416.0f};
        number_config.sprite_id      = qb_sp_numbers_large_yellow;
        number_config.texture_id     = qb_re_t_sprite_large_text;
        number_config.number          = scene_info.level_id - 1;
        auto number_info = factory::ui::create_number(number_config);
        number_info.go_ptr->add_component<flicker_component>();
    }

    void scene_loader::create_loading_qbert(scene_info &scene_info)
    {
		factory::character::player_config_info player_config{};
		player_config.scene_ptr         = scene_info.scene_ptr;
    	player_config.parent_ptr        = scene_info.root_ptr;
		player_config.name              = "qbert";
		player_config.local_position    = {224.0f, 68.0f};
		player_config.sprite_id         = qb_sp_qbert_player_1;
		player_config.texture_id        = qb_re_t_sprite_general;
		player_config.row_idx           = 0;
		player_config.col_idx           = 0;
		player_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_left};
		player_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_right};
		player_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_up};
		player_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::input::k_down};
		auto const player_info = factory::character::create_ai_player(player_config);
    	player_info.go_ptr->add_tag("loading");

    	auto const cube_component_ptrs = scene_info.level_info.cube_info.cube_components;
    	for (auto const &cube_comp_ptr : cube_component_ptrs)
    	{
    		player_info.position_comp_ptr->add_observer(cube_comp_ptr);
    	}
    }

    void scene_loader::create_scoreboard(mngn::scene *scene_ptr)
    {
		auto scores = score_manager::instance().scores();
    	auto saved_score = score_manager::instance().saved_score();
    	bool const is_first = scores.begin()->first == saved_score.first and scores.begin()->second == saved_score.second;
    	
    	// Top score
    	factory::ui::number_config_info number_config{};
    	number_config.scene_ptr      = scene_ptr;
    	number_config.name           = "score_1";
    	number_config.sprite_id      = qb_sp_numbers_regular_orange;
    	number_config.texture_id     = qb_re_t_sprite_general;
    	number_config.local_position = {256.0f, 98.0f};
    	number_config.number		 = scores.begin()->first;
		auto score_info = factory::ui::create_number(number_config);
		score_info.go_ptr->add_tag("score");
    	if (is_first) score_info.go_ptr->add_component<flicker_component>();

    	// Top initial
    	factory::ui::text_config_info text_config{};
    	text_config.scene_ptr        = scene_ptr;
    	text_config.name             = "initial_1";
    	text_config.local_position   = {142.0f, 92.0f};
    	text_config.sprite_id        = qb_sp_alphabet_large_yellow;
    	text_config.texture_id       = qb_re_t_sprite_large_text;
    	text_config.space_sprite_id  = qb_sp_alphabet_large_space;
    	text_config.space_texture_id = qb_re_t_sprite_large_text;
    	text_config.dot_sprite_id    = qb_sp_alphabet_large_special_yellow;
    	text_config.dot_texture_id   = qb_re_t_sprite_large_text;
    	text_config.dot_frame 	     = 0;
    	text_config.text             = scores.begin()->second;
    	auto text_info = factory::ui::create_text(text_config);
    	text_info.go_ptr->add_tag("score");

    	text_config.sprite_id        = qb_sp_alphabet_regular_purple;
    	text_config.texture_id       = qb_re_t_sprite_general;
    	text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
    	text_config.space_texture_id = qb_re_t_sprite_general;
    	text_config.dot_sprite_id    = qb_sp_alphabet_regular_special;
    	text_config.dot_texture_id   = qb_re_t_sprite_general;
    	text_config.dot_frame        = 16;

		constexpr glm::vec2 initial_start_pos{64.0f, 144.0f};
		constexpr glm::vec2 score_start_pos{128.0f, 144.0f};
		constexpr float offset_x = 224.0f;
		constexpr float offset_y = 32.0f;
    	auto it = std::next(scores.begin());
    	for (int i = 0; i < 22; ++i, ++it)
		{
    		bool is_saved = it->first == saved_score.first and it->second == saved_score.second;
    		
    		// Scores
    		int score = it->first;
			number_config.number = score;
			bool const is_even = i % 2 == 0;
  
			float x = score_start_pos.x + (is_even ? 0 : offset_x);
			float y = score_start_pos.y + (i / 2) * offset_y;

    		number_config.name           = "score_" + std::to_string(i + 2);
			number_config.local_position = {x, y};
			score_info                   = factory::ui::create_number(number_config);
			score_info.go_ptr->add_tag("score");
    		if (is_saved) score_info.go_ptr->add_component<flicker_component>();

    		// Initials
    		x = initial_start_pos.x + (is_even ? 0 : offset_x);
    		y = initial_start_pos.y + (i / 2) * offset_y;

    		text_config.name           = "initial_" + std::to_string(i + 2);
    		text_config.local_position = {x, y};
    		text_config.text           = it->second;
    		text_info                  = factory::ui::create_text(text_config);
    		text_info.go_ptr->add_tag("score");
    		if (is_saved) text_info.go_ptr->add_component<flicker_component>();
		}
    }

    void scene_loader::load_countdown(int seconds)
    {
        auto const scene_ptr = mngn::scene_manager::instance().find("input");
    	auto const countdown_go_ptrs = scene_ptr->find_game_objects_with_tag("countdown");
    	for (auto const &countdown_go_ptr : countdown_go_ptrs)
    	{
    		scene_ptr->remove(countdown_go_ptr);
    	}
    	
    	factory::ui::number_config_info number_config{};
    	number_config.scene_ptr      = scene_ptr;
    	number_config.name           = "countdown";
    	number_config.sprite_id      = qb_sp_numbers_regular_orange;
    	number_config.texture_id     = qb_re_t_sprite_general;
    	number_config.local_position = {160.0f, 464.0f};
    	number_config.number		 = seconds;
		auto const number_info = factory::ui::create_number(number_config);
		number_info.go_ptr->add_tag("countdown");
    }

    void scene_loader::load_input_message(int ranking)
    {
        auto scene_ptr = mngn::scene_manager::instance().find("input");
    	auto text_input_ptrs = scene_ptr->find_game_objects_with_tag("text_input");
    	for (auto const &countdown_go_ptr : text_input_ptrs)
    	{
    		scene_ptr->remove(countdown_go_ptr);
    	}

    	if (ranking == 1)
    	{
			factory::ui::text_config_info text_config{};
			text_config.scene_ptr        = scene_ptr;
			text_config.name             = "text_hi_there";
			text_config.local_position   = {50.0f, 40.0f};
			text_config.sprite_id        = qb_sp_alphabet_large_gray;
			text_config.texture_id       = qb_re_t_sprite_large_text;
			text_config.space_sprite_id  = qb_sp_alphabet_large_space;
			text_config.space_texture_id = qb_re_t_sprite_large_text;
			text_config.text             = "you did it";
    		text_config.spacing		     = 4;
			auto text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");

    		factory::ui::sprite_config_info sprite_config{};
    		sprite_config.scene_ptr      = scene_ptr;
    		sprite_config.name           = "text_!";
    		sprite_config.local_position = {410.0f, 40.0f};
    		sprite_config.sprite_id      = qb_sp_alphabet_large_special_gray;
    		sprite_config.texture_id     = qb_re_t_sprite_large_text;
    		sprite_config.curr_frame	 = 1;
    		auto sprite_info = factory::ui::create_sprite(sprite_config);
    		sprite_info.go_ptr->add_tag("text_input");
    		
			text_config.name             = "row_1";
			text_config.local_position   = {80.0f, 112.0f};
			text_config.sprite_id        = qb_sp_alphabet_regular_purple;
			text_config.texture_id       = qb_re_t_sprite_general;
			text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
			text_config.space_texture_id = qb_re_t_sprite_general;
			text_config.text             = "you have usurped all";
    		text_config.spacing		     = 0;
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
    		
			text_config.name           = "row_2";
			text_config.local_position = {80.0f, 128.0f};
			text_config.text           = "others to become the";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
    		
			text_config.name                   = "row_3";
			text_config.local_position         = {128.0f, 160.0f};
			text_config.text                   = "supreme noser!";
			text_config.exclamation_sprite_id  = qb_sp_alphabet_regular_special;
			text_config.exclamation_texture_id = qb_re_t_sprite_general;
			text_config.exclamation_frame      = 0;
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
    		
			text_config.name           = "row_4";
			text_config.local_position = {32.0f, 208.0f};
			text_config.text           = "kindly enter your initials";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
    		
			text_config.name           = "row_5";
			text_config.local_position = {128.0f, 224.0f};
			text_config.text           = "for all to see";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
    		
			std::vector<mngn::sprite*> sprites;
			std::generate_n(std::back_inserter(sprites), 14, []
			{
				auto const sprite_ptr  = mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general);
				sprite_ptr->set_current_frame(11);
				return sprite_ptr;
			});

    		factory::ui::multisprite_config_info multisprite_config{};
    		multisprite_config.scene_ptr      = scene_ptr;
    		multisprite_config.name           = "underline_1";
    		multisprite_config.local_position = {128.0f, 176.0f};
    		multisprite_config.sprites		  = sprites;
    		auto multisprite_info = factory::ui::create_multisprite(multisprite_config);
    		multisprite_info.go_ptr->add_tag("text_input");
    		
    	}
	    else
	    {
			factory::ui::text_config_info text_config{};
			text_config.scene_ptr        = scene_ptr;
			text_config.name             = "text_hi_there";
			text_config.local_position   = {86.0f, 40.0f};
			text_config.sprite_id        = qb_sp_alphabet_large_yellow;
			text_config.texture_id       = qb_re_t_sprite_large_text;
			text_config.space_sprite_id  = qb_sp_alphabet_large_space;
			text_config.space_texture_id = qb_re_t_sprite_large_text;
			text_config.text             = "hi there";
	    	text_config.spacing		     = 4;
			auto text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
	    	
    		factory::ui::sprite_config_info sprite_config{};
    		sprite_config.scene_ptr      = scene_ptr;
    		sprite_config.name           = "text_!";
    		sprite_config.local_position = {374.0f, 40.0f};
    		sprite_config.sprite_id      = qb_sp_alphabet_large_special_yellow;
    		sprite_config.texture_id     = qb_re_t_sprite_large_text;
    		sprite_config.curr_frame	 = 1;
    		auto sprite_info = factory::ui::create_sprite(sprite_config);
    		sprite_info.go_ptr->add_tag("text_input");
	    	
			text_config.name             = "row_1";
			text_config.local_position   = {32.0f, 112.0f};
			text_config.sprite_id        = qb_sp_alphabet_regular_purple;
			text_config.texture_id       = qb_re_t_sprite_general;
			text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
			text_config.space_texture_id = qb_re_t_sprite_general;
	    	text_config.exclamation_sprite_id = qb_sp_alphabet_regular_special;
	    	text_config.exclamation_texture_id = qb_re_t_sprite_general;
	    	text_config.exclamation_frame = 0;
			text_config.text             = "welcome to the noser elite!";
	    	text_config.spacing		     = 0;
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");

			text_config.name             = "row_2";
			text_config.local_position   = {96.0f, 128.0f};
			text_config.text             = "your ranking is";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");

	    	factory::ui::number_config_info number_config{};
	    	number_config.scene_ptr      = scene_ptr;
	    	number_config.name           = "ranking";
	    	number_config.sprite_id      = qb_sp_numbers_regular_orange;
	    	number_config.texture_id     = qb_re_t_sprite_general;
	    	number_config.local_position = {ranking < 10 ? 368.0f : 352.0f, 128.0f};
	    	number_config.number		 = ranking;
	    	auto number_info = factory::ui::create_number(number_config);
	    	number_info.go_ptr->add_tag("text_input");

	    	text_config.name = "row_3";
	    	if (ranking == 2)
	    	{
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "you are second only to one";
	    	}
	    	else if (ranking == 3)
	    	{
	    		
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "you must know something";
	    	}
		    else if (ranking == 4)
		    {
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "you make it look so easy!";
		    }
	    	else if (ranking == 5)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "and outstanding achievement";
	    	}
	    	else if (ranking == 6)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "quite impressive actually";
	    	}
	    	else if (ranking == 7)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "an expert with a joystick!";
	    	}
	    	else if (ranking == 8)
	    	{
				text_config.local_position = {96.0f, 160.0f};
				text_config.text           = "not shabby at all!";
	    	}
	    	else if (ranking == 9)
	    	{
				text_config.local_position = {80.0f, 160.0f};
				text_config.text           = "a potential champion!";
	    	}
	    	else if (ranking == 10)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "you made the top ten club!";
	    	}
	    	else if (ranking == 11)
	    	{
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "just missed the top ten!";
	    	}
	    	else if (ranking == 12)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "you could have done worse!";
	    	}
	    	else if (ranking == 13)
	    	{
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "almost out of the teens!";
	    	}
	    	else if (ranking == 14)
	    	{
				text_config.local_position = {64.0f, 160.0f};
				text_config.text           = "looking good out there!";
	    	}
	    	else if (ranking == 15)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "a truly honorable position";
	    	}
	    	else if (ranking == 16)
	    	{
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "now try and get serious!";
	    	}
	    	else if (ranking == 17)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "its a long ways to the top";
	    	}
	    	else if (ranking == 18)
	    	{
				text_config.local_position = {64.0f, 160.0f};
				text_config.text           = "practice makes perfect!";
	    	}
	    	else if (ranking == 19)
	    	{
				text_config.local_position = {64.0f, 160.0f};
				text_config.text           = "nothing to brag about!";
	    	}
	    	else if (ranking == 20)
	    	{
				text_config.local_position = {32.0f, 160.0f};
				text_config.text           = "almost got into the teens!";
	    	}
	    	else if (ranking == 21)
	    	{
				text_config.local_position = {64.0f, 160.0f};
				text_config.text           = "only    scores to beat";
	    		
				number_config.sprite_id      = qb_sp_numbers_regular_purple;
				number_config.texture_id     = qb_re_t_sprite_general;
				number_config.local_position = {144.0f, 160.0f};
				number_config.number		 = 20;
				number_info = factory::ui::create_number(number_config);
				number_info.go_ptr->add_tag("text_input");
	    		
				sprite_config.local_position = {416.0f, 160.0f};
				sprite_info = factory::ui::create_sprite(sprite_config);
				sprite_info.go_ptr->add_tag("text_input");
	    	}
	    	else if (ranking == 22)
	    	{
				text_config.local_position = {64.0f, 160.0f};
				text_config.text           = "not bad for a beginner!";
	    	}
	    	else if (ranking == 23)
	    	{
				text_config.local_position = {48.0f, 160.0f};
				text_config.text           = "the bottom of the barrel!";
	    	}
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
	    	
			text_config.name             = "row_4";
			text_config.local_position   = {48.0f, 194.0f};
			text_config.text             = "joystick selects letters";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
	    	
			text_config.name           = "row_5";
			text_config.local_position = {48.0f, 208.0f};
			text_config.text           = "either button will enter";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
	    	
			text_config.name           = "row_6";
			text_config.local_position = {48.0f, 240.0f};
			text_config.text           = "use   to      use   when";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");
	    	
			text_config.name           = "row_7";
			text_config.local_position = {144.0f, 256.0f};
			text_config.text           = "erase         done";
			text_info = factory::ui::create_text(text_config);
			text_info.go_ptr->add_tag("text_input");

	    	sprite_config.scene_ptr      = scene_ptr;
	    	sprite_config.name           = "text_rub";
	    	sprite_config.local_position = {112.0f, 240.0f};
	    	sprite_config.sprite_id      = qb_sp_text_rub;
	    	sprite_config.texture_id     = qb_re_t_sprite_general;
	    	sprite_config.curr_frame	 = 0;
	    	sprite_info = factory::ui::create_sprite(sprite_config);
	    	sprite_info.go_ptr->add_tag("text_input");
	    	
	    	sprite_config.name           = "text_end";
	    	sprite_config.local_position = {336.0f, 240.0f};
	    	sprite_config.sprite_id      = qb_sp_text_end;
	    	sprite_info = factory::ui::create_sprite(sprite_config);
	    	sprite_info.go_ptr->add_tag("text_input");
	    }
    }
}
