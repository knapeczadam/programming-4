#include "level_loading_state.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/audio_player.h"
#include "core/level_config_manager.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
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
        scene_ptr_ = mngn::scene_manager::instance().find(std::to_string(progress_manager::instance().level()) + "_loading");
        scene_ptr_->set_active(true);
    	scene_ptr_->set_tag("current");
    	qbert_ptr_ = scene_ptr_->find("qbert");
        
        mngn::renderer::instance().set_background_color({});
    	init_events();

    	total_time_ = events_.size() * jump_time_ + intro_time_ + outro_time_;

        switch (progress_manager::instance().level())
        {
        case 1:
	        audio_player::instance().play(audio::level_1);
	        break;
        case 2:
	        audio_player::instance().play(audio::level_2);
	        break;
        case 3:
        	audio_player::instance().play(audio::level_3);
        	break;
        }
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
        	auto const event = events_.front();
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
    	scene_utility::instance().trigger_root();
    	scene_ptr_->clear_tag();
        scene_ptr_->set_active(false);
    }

	void level_loading_state::init_events()
	{
    	auto const level = progress_manager::instance().level();
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
    		auto const direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(-1, -1);
    		auto const player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_right_event()
    {
    	auto f = [this]()
    	{
    		auto const direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(1, 1);
    		auto const player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_up_event()
    {
    	auto f = [this]()
    	{
    		auto const direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(-1, 0);
    		auto const player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    	};
    	events_.emplace(f);
    }

    void level_loading_state::push_down_event()
    {
    	auto f = [this]()
    	{
    		auto const direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(1, 0);
    		auto const player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    	};
    	events_.emplace(f);
    }
}
