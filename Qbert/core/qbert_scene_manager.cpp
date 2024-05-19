#include "qbert_scene_manager.h"

// Project includes
#include "level_config_manager.h"
#include "component/character/position_component.h"
#include "component/level/cube_component.h"
#include "component/level/level_manager_component.h"
#include "component/player/health_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/player_collider_component.h"
#include "component/player/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "core/factory.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/game_component_commands.h"
#include "input/generic_commands.h"
#include "minigin/core/game_object.h"
#include "minigin/core/resource_manager.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/input/input_manager.h"

// Standard includes
#include <ranges>

namespace qbert
{
    void qbert_scene_manager::load_scenes()
    {
#ifndef NDEBUG
    	load_debug_scene();
#endif
        load_menu_scene();
        load_loading_scene();
        load_solo_scene();
        load_duo_scene();
        load_versus_scene();
        load_game_over_scene();
        load_scoreboard_scene();
    	load_game_state_scene();
    }

    void qbert_scene_manager::load_debug_scene()
    {
		auto const font_ptr = mngn::resource_manager::instance().load_font("fonts/Lingua.otf", 10);
		auto const scene_ptr = mngn::scene_manager::instance().create_scene("debug");
		factory::ui::fps_config_info fps_config{};
		fps_config.scene_ptr      = scene_ptr;
		fps_config.name           = "fps";
		fps_config.local_position = {10.0f,      500.0f};
		fps_config.font_ptr       = font_ptr;
		fps_config.text		      = "FPS: ";
		factory::ui::create_fps(fps_config);
    	
		auto debug_command_ptr = std::make_unique<debug_command>();
		mngn::input_manager::instance().bind_command(mngn::input_type::keyboard, mngn::input_state::down, mngn::k_j, std::move(debug_command_ptr));
    }

    void qbert_scene_manager::load_game_state_scene()
    {
		auto const scene_ptr = mngn::scene_manager::instance().create_scene("game_state");
	    auto go_ptr = scene_ptr->create_game_object("game_state");
	    auto game_state_comp_ptr = go_ptr->add_component<game_state_component>();

	    auto solo_command = std::make_unique<game_mode_command>(game_state_comp_ptr, 0);
	    auto duo_command = std::make_unique<game_mode_command>(game_state_comp_ptr, 1);
	    auto versus_command = std::make_unique<game_mode_command>(game_state_comp_ptr, 2);

		mngn::input_manager::instance().bind_command(mngn::input_type::keyboard, mngn::input_state::down, mngn::k_1, std::move(solo_command));
		mngn::input_manager::instance().bind_command(mngn::input_type::keyboard, mngn::input_state::down, mngn::k_2, std::move(duo_command));
		mngn::input_manager::instance().bind_command(mngn::input_type::keyboard, mngn::input_state::down, mngn::k_3, std::move(versus_command));
    }

    void qbert_scene_manager::load_menu_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("menu");
        scene_ptr->set_active(false);
        
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "text_qbert";
        sprite_config.local_position = {38, 36};
        sprite_config.sprite_id      = qb_sp_text_qbert;
        factory::ui::create_sprite(sprite_config);

        factory::ui::text_config_info text_config{};
        text_config.scene_ptr       = scene_ptr;
        text_config.name            = "credits";
        text_config.local_position  = {338, 66};
        text_config.text            = "credits";
        text_config.sprite_id       = qb_sp_alphabet_regular_green;
        text_config.texture_id      = qb_re_t_sprite_general;
        text_config.space_sprite_id = qb_sp_alphabet_regular_space;
        factory::ui::create_text(text_config);

        text_config.name = "row_1";
        text_config.local_position = {98, 114};
        text_config.text = "jump on squares to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_2";
        text_config.local_position = {98, 130};
        text_config.text = "change them to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_3";
        text_config.local_position = {98, 146};
        text_config.text = "the target color";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_4";
        text_config.local_position = {114, 178};
        text_config.text = "stay on playfield";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_5";
        text_config.local_position = {114, 194};
        text_config.text = "jumping off results";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_6";
        text_config.local_position = {114, 210};
        text_config.text = "in a fatal plummet";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_7";
        text_config.local_position = {114, 226};
        text_config.text = "unless a disk is there";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_8";
        text_config.local_position = {130, 258};
        text_config.text = "avoid all objects";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_9";
        text_config.local_position = {130, 274};
        text_config.text = "and creatures that";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_10";
        text_config.local_position = {130, 290};
        text_config.text = "are not green";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_11";
        text_config.local_position = {146, 322};
        text_config.text = "use spinning disks";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_12";
        text_config.local_position = {146, 338};
        text_config.text = "to lure snake to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_14";
        text_config.local_position = {146, 354};
        text_config.text = "his death";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_15";
        text_config.local_position = {162, 386};
        text_config.text = "extra life at";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_16";
        text_config.local_position = {258, 402};
        text_config.text = "and each";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_17";
        text_config.local_position = {162, 418};
        text_config.text = "additional";
        factory::ui::create_text(text_config);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr;
        number_config.name           = "number_1";
        number_config.local_position = {176, 402};
        number_config.number         = 8000;
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_number(number_config);
        
        number_config.name           = "number_2";
        number_config.local_position = {336, 418};
        number_config.number         = 14000;
        factory::ui::create_number(number_config);
    }

    void qbert_scene_manager::load_loading_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("loading");
        scene_ptr->set_active(false);
    	
		factory::ui::text_config_info text_config{};
		text_config.scene_ptr      = scene_ptr;
		text_config.name           = "text_loading";
		text_config.local_position = {176.0f, 288.0f};
		text_config.sprite_id      = qb_sp_alphabet_regular_purple;
		text_config.texture_id     = qb_re_t_sprite_general;
		text_config.space_sprite_id = qb_sp_alphabet_regular_space;
		text_config.space_texture_id = qb_re_t_sprite_general;
		text_config.text           = "loading";
		factory::ui::create_flickering_text(text_config);
    }

    void qbert_scene_manager::load_solo_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("solo");
    	scene_ptr->set_active(false);
    	
        //---------------------------------------------------------------------------------
        // ROOT
        //---------------------------------------------------------------------------------
        auto root_ptr = scene_ptr->create_game_object("root");
        auto level_manager_comp_ptr = root_ptr->add_component<level_manager_component>();

    	//---------------------------------------------------------------------------------
    	// UI
    	//---------------------------------------------------------------------------------
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "text_player_1";
        sprite_config.local_position = {32, 32};
        sprite_config.sprite_id      = qb_sp_text_purple_player;
        sprite_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_1";
        sprite_config.local_position = {144, 16};
        sprite_config.sprite_id      = qb_sp_text_one;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name = "text_change_to";
        sprite_config.local_position = {32, 80};
        sprite_config.sprite_id      = qb_sp_text_change_to;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name = "text_level";
        sprite_config.local_position = {368, 80};
        sprite_config.sprite_id      = qb_sp_text_level;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_round";
        sprite_config.local_position = {368, 96};
        sprite_config.sprite_id      = qb_sp_text_round;
        factory::ui::create_sprite(sprite_config);
        
        factory::ui::arrow_config_info arrow_config{};
        arrow_config.scene_ptr      = scene_ptr;
        arrow_config.name           = "left_arrow_1";
        arrow_config.local_position = {32, 96};
        arrow_config.sprite_id      = qb_sp_arrow_right;
        arrow_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = "left_arrow_2";
        arrow_config.local_position = {48, 96};
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);    
        
        arrow_config.name           = "right_arrow_1";
        arrow_config.local_position = {96, 96};
        arrow_config.sprite_id      = qb_sp_arrow_left;
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = "right_arrow_2";
        arrow_config.local_position = {112, 96};
        arrow_config.delay          = 0.0f;
        factory::ui::create_arrow(arrow_config);
    	
		factory::ui::score_display_config_info score_display_config{};
		score_display_config.scene_ptr      = scene_ptr;
		score_display_config.parent_ptr     = root_ptr;
		score_display_config.name           = "score_1";
		score_display_config.local_position = {32.0f,    48.0f};
		score_display_config.sprite_id	  = qb_sp_numbers_regular_orange;
		score_display_config.texture_id     = qb_re_t_sprite_general;
		auto score_display_info_1 = factory::ui::create_score_display(score_display_config);
	
		factory::ui::health_display_config_info health_display_config{};
		health_display_config.scene_ptr      = scene_ptr;
		health_display_config.parent_ptr     = root_ptr;
		health_display_config.name           = "health_1";
		health_display_config.local_position = {16.0f, 160.0f};
		auto heal_display_info_1 = factory::ui::create_health_display(health_display_config);
	
		factory::ui::level_display_config_info level_display_config{};
		level_display_config.scene_ptr      = scene_ptr;
		level_display_config.parent_ptr     = root_ptr;
		level_display_config.name           = "numbers_level";
		level_display_config.local_position = {432.0f, 80.0f};
		level_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		level_display_config.texture_id     = qb_re_t_sprite_general;
		auto level_display_info = factory::ui::create_level_display(level_display_config);

		factory::ui::round_display_config_info round_display_config{};
		round_display_config.scene_ptr      = scene_ptr;
		round_display_config.parent_ptr     = root_ptr;
		round_display_config.name           = "round";
		round_display_config.local_position = {432.0f, 96.0f};
		round_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		round_display_config.texture_id     = qb_re_t_sprite_general;
		auto round_display_info = factory::ui::create_round_display(round_display_config);

        // ---------------------------------------------------------------------------------
        // LEVEL
        //---------------------------------------------------------------------------------
        factory::level::level_config_info level_config{};
        level_config.scene_ptr    = scene_ptr;
        level_config.parent_ptr   = root_ptr;
        level_config.level_id     = 1;
        level_config.level_config = level_config_manager::instance().get_level_config();
        auto level_info = factory::level::create_level(level_config);

		//---------------------------------------------------------------------------------
		// PLAYER 1
		//---------------------------------------------------------------------------------
		factory::character::player_config_info player_1_config{};
		player_1_config.scene_ptr         = scene_ptr;
		player_1_config.parent_ptr        = root_ptr;
		player_1_config.name              = "player_1";
		player_1_config.local_position    = {224.0f, 84.0f};
		player_1_config.sprite_id         = qb_sp_qbert_player_1;
		player_1_config.texture_id        = qb_re_t_sprite_general;
		player_1_config.row_idx           = 0;
		player_1_config.col_idx           = 0;
		player_1_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_left};
		player_1_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_right};
		player_1_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_up};
		player_1_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_down};
		player_1_config.left_command_alt  = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_left};
		player_1_config.right_command_alt = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_right};
		player_1_config.up_command_alt    = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_up};
		player_1_config.down_command_alt  = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_down};
		// Observers
		auto player_1_info = factory::character::create_player(player_1_config);
		mngn::collision_manager::instance().register_collider(player_1_info.collider_comp_ptr);
		player_1_info.health_comp_ptr->add_observer(heal_display_info_1.health_display_comp_ptr);
		player_1_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
		player_1_info.score_counter_comp_ptr->add_observer(score_display_info_1.score_display_comp_ptr);
		player_1_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
		player_1_info.level_counter_comp_ptr->add_observer(level_display_info.level_display_comp_ptr);
		player_1_info.round_counter_comp_ptr->add_observer(round_display_info.round_display_comp_ptr);
		std::ranges::for_each(level_info.cube_info.cube_components, [player_1_info](auto cube_comp_ptr) { player_1_info.position_comp_ptr->add_observer(cube_comp_ptr); });

		//---------------------------------------------------------------------------------
		// ENEMY
		//---------------------------------------------------------------------------------
		// Red Ball
		factory::character::red_ball_config_info red_ball_config{};
		red_ball_config.scene_ptr      = scene_ptr;
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
		coily_config.scene_ptr      = scene_ptr;
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
		ugg_config.scene_ptr      = scene_ptr;
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
		wrong_way_config.scene_ptr      = scene_ptr;
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
		green_ball_config.scene_ptr  = scene_ptr;
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
		slick_config.scene_ptr  = scene_ptr;
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
		sam_config.scene_ptr  = scene_ptr;
		sam_config.parent_ptr = root_ptr;
		sam_config.name       = "sam_1";
		sam_config.sprite_id  = qb_sp_sam;
		sam_config.texture_id = qb_re_t_sprite_general;
		auto sam_info = factory::character::create_sam(sam_config);
		// Observers
		sam_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
		sam_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
		std::ranges::for_each(level_info.cube_info.cube_components, [sam_info](auto cube_comp_ptr) { sam_info.position_comp_ptr->add_observer(cube_comp_ptr); });
    }

    void qbert_scene_manager::load_duo_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("duo");
        scene_ptr->set_active(false);
    	
        //---------------------------------------------------------------------------------
        // ROOT
        //---------------------------------------------------------------------------------
        auto root_ptr = scene_ptr->create_game_object("root");
        auto level_manager_comp_ptr = root_ptr->add_component<level_manager_component>();

    	//---------------------------------------------------------------------------------
    	// UI
    	//---------------------------------------------------------------------------------
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr;
        sprite_config.name           = "text_player_1";
        sprite_config.local_position = {32, 32};
        sprite_config.sprite_id      = qb_sp_text_purple_player;
        sprite_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_player_2";
        sprite_config.local_position = {332, 32};
        sprite_config.sprite_id      = qb_sp_text_orange_player;
        sprite_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_1";
        sprite_config.local_position = {144, 16};
        sprite_config.sprite_id      = qb_sp_text_one;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_2";
        sprite_config.local_position = {444, 16};
        sprite_config.sprite_id      = qb_sp_text_two;
        factory::ui::create_sprite(sprite_config);

        sprite_config.name = "text_change_to";
        sprite_config.local_position = {32, 80};
        sprite_config.sprite_id      = qb_sp_text_change_to;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name = "text_level";
        sprite_config.local_position = {368, 80};
        sprite_config.sprite_id      = qb_sp_text_level;
        factory::ui::create_sprite(sprite_config);
        
        sprite_config.name           = "text_round";
        sprite_config.local_position = {368, 96};
        sprite_config.sprite_id      = qb_sp_text_round;
        factory::ui::create_sprite(sprite_config);
        
        factory::ui::arrow_config_info arrow_config{};
        arrow_config.scene_ptr      = scene_ptr;
        arrow_config.name           = "left_arrow_1";
        arrow_config.local_position = {32, 96};
        arrow_config.sprite_id      = qb_sp_arrow_right;
        arrow_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = "left_arrow_2";
        arrow_config.local_position = {48, 96};
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);    
        
        arrow_config.name           = "right_arrow_1";
        arrow_config.local_position = {96, 96};
        arrow_config.sprite_id      = qb_sp_arrow_left;
        arrow_config.delay          = 0.2f;
        factory::ui::create_arrow(arrow_config);
        
        arrow_config.name           = "right_arrow_2";
        arrow_config.local_position = {112, 96};
        arrow_config.delay          = 0.0f;
        factory::ui::create_arrow(arrow_config);
    	
		factory::ui::score_display_config_info score_display_config{};
		score_display_config.scene_ptr      = scene_ptr;
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
		health_display_config.scene_ptr      = scene_ptr;
		health_display_config.parent_ptr     = root_ptr;
		health_display_config.name           = "health_1";
		health_display_config.local_position = {16.0f, 160.0f};
		auto heal_display_info_1 = factory::ui::create_health_display(health_display_config);
	
		health_display_config.name           = "health_2";
		health_display_config.local_position = {448.0f, 160.0f};
		auto heal_display_info_2 = factory::ui::create_health_display(health_display_config);

		factory::ui::level_display_config_info level_display_config{};
		level_display_config.scene_ptr      = scene_ptr;
		level_display_config.parent_ptr     = root_ptr;
		level_display_config.name           = "numbers_level";
		level_display_config.local_position = {432.0f, 80.0f};
		level_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		level_display_config.texture_id     = qb_re_t_sprite_general;
		auto level_display_info = factory::ui::create_level_display(level_display_config);

		factory::ui::round_display_config_info round_display_config{};
		round_display_config.scene_ptr      = scene_ptr;
		round_display_config.parent_ptr     = root_ptr;
		round_display_config.name           = "round";
		round_display_config.local_position = {432.0f, 96.0f};
		round_display_config.sprite_id      = qb_sp_numbers_regular_orange;
		round_display_config.texture_id     = qb_re_t_sprite_general;
		auto round_display_info = factory::ui::create_round_display(round_display_config);
    	
        // ---------------------------------------------------------------------------------
        // LEVEL
        //---------------------------------------------------------------------------------
        factory::level::level_config_info level_config{};
        level_config.scene_ptr    = scene_ptr;
        level_config.parent_ptr   = root_ptr;
        level_config.level_id     = 1;
        level_config.level_config = level_config_manager::instance().get_level_config();
        auto level_info = factory::level::create_level(level_config);

		//---------------------------------------------------------------------------------
		// PLAYER 1
		//---------------------------------------------------------------------------------
		factory::character::player_config_info player_1_config{};
		player_1_config.scene_ptr         = scene_ptr;
		player_1_config.parent_ptr        = root_ptr;
		player_1_config.name              = "player_1";
		player_1_config.local_position    = {224.0f, 84.0f};
		player_1_config.sprite_id         = qb_sp_qbert_player_1;
		player_1_config.texture_id        = qb_re_t_sprite_general;
		player_1_config.row_idx           = 0;
		player_1_config.col_idx           = 0;
		player_1_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_left};
		player_1_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_right};
		player_1_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_up};
		player_1_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_down};
		player_1_config.left_command_alt  = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_left};
		player_1_config.right_command_alt = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_right};
		player_1_config.up_command_alt    = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_up};
		player_1_config.down_command_alt  = {mngn::input_type::controller, mngn::input_state::pressed, mngn::c_down};
		// Observers
		auto player_1_info = factory::character::create_player(player_1_config);
		mngn::collision_manager::instance().register_collider(player_1_info.collider_comp_ptr);
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
		player_2_config.scene_ptr      = scene_ptr;
		player_2_config.parent_ptr  = root_ptr;
		player_2_config.name           = "player_2";
		player_2_config.local_position = {32.0f, 372.0f};
		player_2_config.sprite_id      = qb_sp_qbert_player_2;
		player_2_config.texture_id     = qb_re_t_sprite_general;
		player_2_config.row_idx        = 6;
		player_2_config.col_idx        = 0;
		player_2_config.left_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_a};
		player_2_config.right_command  = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_d};
		player_2_config.up_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_w};
		player_2_config.down_command   = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_s};
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
		red_ball_config.scene_ptr      = scene_ptr;
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
		coily_config.scene_ptr      = scene_ptr;
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
		ugg_config.scene_ptr      = scene_ptr;
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
		wrong_way_config.scene_ptr      = scene_ptr;
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
		green_ball_config.scene_ptr  = scene_ptr;
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
		slick_config.scene_ptr  = scene_ptr;
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
		sam_config.scene_ptr  = scene_ptr;
		sam_config.parent_ptr = root_ptr;
		sam_config.name       = "sam_1";
		sam_config.sprite_id  = qb_sp_sam;
		sam_config.texture_id = qb_re_t_sprite_general;
		auto sam_info = factory::character::create_sam(sam_config);
		// Observers
		sam_info.position_comp_ptr->add_observer(level_manager_comp_ptr);
		sam_info.health_comp_ptr->add_observer(level_manager_comp_ptr);
		std::ranges::for_each(level_info.cube_info.cube_components, [sam_info](auto cube_comp_ptr) { sam_info.position_comp_ptr->add_observer(cube_comp_ptr); });
    }

    void qbert_scene_manager::load_versus_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("versus");
        scene_ptr->set_active(false);
    }

    void qbert_scene_manager::load_game_over_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("game_over");
        scene_ptr->set_active(false);
    	
		factory::ui::text_config_info text_config{};
		text_config.scene_ptr      = scene_ptr;
		text_config.name           = "text_game_over";
		text_config.local_position = {176.0f, 288.0f};
		text_config.sprite_id      = qb_sp_alphabet_regular_purple;
		text_config.texture_id     = qb_re_t_sprite_general;
		text_config.space_sprite_id = qb_sp_alphabet_regular_space;
		text_config.space_texture_id = qb_re_t_sprite_general;
		text_config.text           = "game over";
		factory::ui::create_flickering_text(text_config);
    }

    void qbert_scene_manager::load_scoreboard_scene()
    {
        auto scene_ptr = mngn::scene_manager::instance().create_scene("scoreboard");
        scene_ptr->set_active(false);
    	
		factory::ui::text_config_info text_config{};
		text_config.scene_ptr      = scene_ptr;
		text_config.name           = "text_scoreboard";
		text_config.local_position = {176.0f, 288.0f};
		text_config.sprite_id      = qb_sp_alphabet_regular_purple;
		text_config.texture_id     = qb_re_t_sprite_general;
		text_config.space_sprite_id = qb_sp_alphabet_regular_space;
		text_config.space_texture_id = qb_re_t_sprite_general;
		text_config.text           = "scoreboard";
		factory::ui::create_flickering_text(text_config);
    }
}
