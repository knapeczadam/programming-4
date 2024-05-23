#include "level_loading_state.h"

// Project includes
#include "component/character/position_component.h"
#include "component/state/game_state_component.h"
#include "component/level/cube_component.h"
#include "minigin/core/game_object.h"
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/factory.h"
#include "core/level_config_manager.h"
#include "core/progress_manager.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/input/input_manager.h"
#include "state/game/coop_state.h"
#include "state/player/jumping_state.h"

namespace qbert
{
    level_loading_state::level_loading_state(game_state_component* game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void level_loading_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("loading");
        scene_ptr_->set_active(true);
        
        mngn::renderer::instance().set_background_color({});
        load_sprites();
        load_cubes();
    	load_qbert();
    	init_events();

    	total_time_ = events_.size() * jump_time_ + intro_time_ + outro_time_;
    }

    void level_loading_state::update()
    {
    	accu_time_intro_ += mngn::game_time::instance().delta_time();
    	if (accu_time_intro_ < intro_time_)
		{
			return;
		}
    	
    	accu_time_total_ += mngn::game_time::instance().delta_time();
        accu_time_jump_ += mngn::game_time::instance().delta_time();
        if (accu_time_jump_ > jump_time_ and not events_.empty())
        {
        	auto event = events_.front();
        	events_.pop();
        	event();
        	accu_time_jump_ = 0.0f;
        }
		if (accu_time_total_ >= total_time_)
    	{
			accu_time_intro_ = 0.0f;
			accu_time_jump_  = 0.0f;
			accu_time_total_ = 0.0f;
            game_state_comp_ptr_->load_game_mode();
    	}
    }

    void level_loading_state::on_exit()
    {
        clean_up();
        scene_ptr_->set_active(false);
    }

    void level_loading_state::load_sprites()
    {
    	auto level = progress_manager::instance().level();
    	
		factory::ui::sprite_config_info sprite_config{};
    	sprite_config.scene_ptr      = scene_ptr_;
    	sprite_config.name           = "level";
    	sprite_config.local_position = {48.0f, 288.0f};
    	sprite_config.sprite_id      = level + 10000;
    	sprite_config.texture_id     = qb_re_t_sprite_general;
    	factory::ui::create_sprite(sprite_config);

        sprite_config.name = "green_circle";
        sprite_config.local_position = {208.0f, 400.0f};
        sprite_config.sprite_id = qb_sp_green_cirlce;
        factory::ui::create_sprite(sprite_config);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr_;
        number_config.name           = "level_number";
        number_config.local_position = {226.0f, 416.0f};
        number_config.sprite_id      = qb_sp_numbers_large_yellow;
        number_config.texture_id     = qb_re_t_sprite_large_text;
        number_config.number          = level - 1;
        auto number_info = factory::ui::create_number(number_config);
        number_info.go_ptr->add_component<flicker_component>();
    }

    void level_loading_state::load_cubes()
    {
    	auto level = progress_manager::instance().level();
        auto config = level_config_manager::instance().get_level_config();

        for (auto const &level_config : config["levels"])
        {
            if (level_config["level_id"] == level)
            {
                
                factory::level::cube_config_info cube_config{};
                cube_config.scene_ptr      = scene_ptr_;
                cube_config.name           = "cube_1";
                cube_config.local_position = {208.0f, 80.0f};
                cube_config.texture_id     = qb_re_t_sprite_general;
                cube_config.color_1    = level_config["cube_color_1"];
                cube_config.color_2    = level_config["cube_color_2"];
                if (level_config.contains("cube_color_3")) cube_config.color_3 = level_config["cube_color_3"];
                if (level_config.contains("cube_revertible")) cube_config.revertible = level_config["cube_revertible"];
                cube_config.row_idx = 0;
                cube_config.col_idx = 0;
                auto cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
                
                cube_config.name           = "cube_2";
                cube_config.local_position = {176.0f, 128.0f};
                cube_config.row_idx = 1;
                cube_config.col_idx = 0;
                cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
                
                cube_config.name           = "cube_3";
                cube_config.local_position = {240.0f, 128.0f};
                cube_config.row_idx = 1;
                cube_config.col_idx = 1;
                cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");
                
                cube_config.name           = "cube_4";
                cube_config.local_position = {208.0f, 176.0f};
                cube_config.row_idx = 2;
                cube_config.col_idx = 1;
                cube_info = factory::level::create_cube(cube_config);
                cube_info.go_ptr->add_tag("cube");

            	break;
            }
        }
    }

    void level_loading_state::load_qbert()
    {
		factory::character::player_config_info player_config{};
		player_config.scene_ptr         = scene_ptr_;
		player_config.name              = "qbert";
		player_config.local_position    = {224.0f, 68.0f};
		player_config.sprite_id         = qb_sp_qbert_player_1;
		player_config.texture_id        = qb_re_t_sprite_general;
		player_config.row_idx           = 0;
		player_config.col_idx           = 0;
		player_config.left_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_left};
		player_config.right_command     = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_right};
		player_config.up_command        = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_up};
		player_config.down_command      = {mngn::input_type::keyboard, mngn::input_state::down, mngn::k_down};
		auto player_info = factory::character::create_ai_player(player_config);
    	qbert_ptr_ = player_info.go_ptr;

    	auto cubes = scene_ptr_->find_game_objects_with_tag("cube");
    	for (auto const &cube : cubes)
    	{
    		auto cube_comp_ptr = cube->component<cube_component>();
    		player_info.position_comp_ptr->add_observer(cube_comp_ptr);
    	}
    }

    void level_loading_state::clean_up()
    {
        auto cube_go_ptrs = scene_ptr_->find_game_objects_with_tag("cube");
        for (auto const &cube_ptr : cube_go_ptrs)
        {
            scene_ptr_->remove(cube_ptr);
        }

        auto level_go_ptr = scene_ptr_->find("level");
        if (level_go_ptr) scene_ptr_->remove(level_go_ptr);
        auto number_go_ptr = scene_ptr_->find("level_number");
        if (number_go_ptr) scene_ptr_->remove(number_go_ptr);
    	auto qbert_go_ptr = scene_ptr_->find("qbert");
    	if (qbert_go_ptr) scene_ptr_->remove(qbert_go_ptr);
    }

	void level_loading_state::init_events()
	{
    	auto level = progress_manager::instance().level();
	    switch (level)
	    {
	    case 1:
		    {
	    		push_right_event();
	    		push_left_event();
	    		push_down_event();
	    		push_up_event();
		    }
	    	break;
	    case 2:
		    {
	    		push_right_event();
	    		push_down_event();
	    		push_left_event();
	    		push_right_event();
	    		push_up_event();
	    		push_down_event();
		    }
	    	break;
	    case 3:
		    {
			    push_right_event();
	    		push_down_event();
	    		push_left_event();
	    		push_up_event();
	    		push_down_event();
	    		push_right_event();
	    		push_up_event();
		    }
	    	break;
	    default:
		    {
	    		push_down_event();
	    		push_right_event();
	    		push_left_event();
	    		push_up_event();
	    		push_down_event();
	    		push_right_event();
	    		push_left_event();
	    		push_up_event();
	    		push_down_event();
		    }
	    }
	}

    void level_loading_state::push_left_event()
    {
    	auto f = [this]()
    	{
    		auto direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(-1, -1);
    		auto player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    		
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_right_event()
    {
    	auto f = [this]()
    	{
    		auto direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(1, 1);
    		auto player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    		
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_up_event()
    {
    	auto f = [this]()
    	{
    		auto direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(-1, 0);
    		auto player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    		
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_down_event()
    {
    	auto f = [this]()
    	{
    		auto direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(1, 0);
    		auto player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    		
    	};
    	events_.emplace(f);
    }
}
