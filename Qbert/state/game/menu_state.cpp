#include "menu_state.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "component/ui/number_component.h"
#include "core/audio_player.h"
#include "core/factory.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/utility/math.h"
#include "minigin/utility/sprite.h"
#include "state/player/idle_state.h"
#include "state/player/jumping_state.h"

namespace qbert
{
    menu_state::menu_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void menu_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("menu");
        scene_ptr_->set_active(true);
        scene_ptr_->set_tag("current");
        scene_ptr_ = mngn::scene_manager::instance().find("menu_1");
        scene_ptr_->set_active(true);

        mngn::renderer::instance().set_background_color({49, 32, 115, 0});

        disk_ptr_ = scene_ptr_->find("disk");
        disk_ptr_->set_local_position(qbert_start_pos_);

        audio_player::instance().play(audio::hello);

        switch_time_ = switch_times_[menu_idx_];
    }

    void menu_state::update()
    {
        accu_time_switch_ += mngn::game_time::instance().delta_time();
        if (accu_time_switch_ >= switch_time_)
        {
            accu_time_switch_ = 0.0f;
            switch_menu();
        }

        if (menu_idx_ == 0)
        {
            animate_flying_qbert();
        }
        else if (menu_idx_ == 1)
        {
            animate_jumping_qbert();
        }
    }

    void menu_state::on_exit()
    {
        accu_time_switch_ = 0.0f;
        menu_idx_         = 0;
        disk_ptr_->set_local_position(qbert_start_pos_);
        
        progress_manager::instance().reset();
        score_manager::instance().reset();
        
        progress_manager::instance().use_coin();
        auto number_comp_ptr = scene_utility::instance().current_scene()->find_game_objects_with_tag("coin").front()->component<number_component>();
        number_comp_ptr->set_number(progress_manager::instance().coins());
        
        auto scene_ptr = scene_utility::instance().current_scene();
        scene_ptr->clear_tag();
        scene_ptr->set_active(false);
        
        scene_ptr_->set_active(false);
    }

    void menu_state::switch_menu()
    {
        menu_idx_ = (menu_idx_ + 1) % 3;
        switch_time_ = switch_times_[menu_idx_];
        
        switch (menu_idx_)
        {
        case 0:
            scene_ptr_ = mngn::scene_manager::instance().find("menu_2");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_3");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_1");
            scene_ptr_->set_active(true);
            audio_player::instance().play(audio::hello);
            break;
        case 1:
            scene_ptr_ = mngn::scene_manager::instance().find("menu_1");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_3");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_2");
            scene_ptr_->set_active(true);
            init_events();
            break;
        case 2:
            scene_ptr_ = mngn::scene_manager::instance().find("menu_1");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_2");
            scene_ptr_->set_active(false);
            scene_ptr_ = mngn::scene_manager::instance().find("menu_3");
            scene_ptr_->set_active(true);
            break;
        }
    }

    void menu_state::animate_flying_qbert()
    {
        glm::vec2 curr_pos = disk_ptr_->local_position();
        if (curr_pos != qbert_end_pos_)
        {
            curr_pos = glm::mix(qbert_start_pos_, qbert_end_pos_, glm::clamp(accu_time_switch_ / switch_time_, 0.0f, 1.0f));
            disk_ptr_->set_local_position(curr_pos);
        }
        else
        {
            disk_ptr_->set_local_position(qbert_start_pos_);
        }
    }

    void menu_state::animate_jumping_qbert()
    {
        accu_time_jump_ += mngn::game_time::instance().delta_time();
        accu_time_ball_ += mngn::game_time::instance().delta_time();
        
        if (accu_time_jump_ > jump_time_ and not events_.empty())
        {
            auto event = events_.front();
            events_.pop();
            event();
            accu_time_jump_ = 0.0f;
        }
        
        if (accu_time_ball_ > ball_time_)
        {
            accu_time_ball_ = 0.0f;
            ball_falling_ = true;
            ball_ptr_->set_active(true);
        }
        
        if (ball_falling_)
        {
            glm::vec2 curr_pos = ball_ptr_->local_position();
            if (curr_pos != ball_bump_pos_)
            {
                accu_time_fall_ += mngn::game_time::instance().delta_time();
                curr_pos = glm::mix(ball_start_pos_, ball_bump_pos_, glm::clamp(accu_time_fall_ / ball_fall_time_, 0.0f, 1.0f));
                ball_ptr_->set_local_position(curr_pos);
            }
            else
            {
                ball_falling_ = false;
                accu_time_fall_ = 0.0f;
                swearing_ = true;
                audio_player::instance().play(audio::ball_bump);
                qbert_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(4);
            }
        }
        
        if (swearing_)
        {
            accu_time_bump_ += mngn::game_time::instance().delta_time();
            accu_time_fall_ += mngn::game_time::instance().delta_time();
            
            if (accu_time_bump_ > bump_time_)
            {
                swearing_ = false;
                scene_ptr_->find("swearing", true)->set_active(true);
                qbert_ptr_->component<mngn::sprite_component>()->sprite()->set_current_frame(5);
                audio_player::instance().play(audio::qbert_swearing_3);
            }
            
            float t = glm::clamp(accu_time_fall_ / ball_fall_time_, 0.0f, 1.0f);
            glm::vec2 curr_pos_ = mngn::bezier_curve(ball_bump_pos_, ball_pos_1_, ball_pos_2_, ball_end_pos_, t);
            ball_ptr_->set_local_position(curr_pos_);

            if (curr_pos_ == ball_end_pos_) ball_ptr_->set_active(false);
        }
    }

    void menu_state::init_events()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("menu_2");
        qbert_ptr_ = scene_ptr_->find("qbert");
        qbert_ptr_->set_local_position(26.0f, 86.0f);

        ball_ptr_ = scene_ptr_->find("red_ball", true);
        ball_ptr_->set_local_position(ball_start_pos_);

        jump_count_ = 0;
        accu_time_jump_ = 2.0f;
        accu_time_ball_ = 0.0f;
        accu_time_fall_ = 0.0f;
        accu_time_bump_ = 0.0f;

        ball_falling_ = false;
        swearing_     = false;
        scene_ptr_->find("swearing", true)->set_active(false);

        events_ = std::queue<std::function<void()>>{};
        push_right_event();
        push_right_event();
        push_right_event();
        push_right_event();
        push_right_event();
        
        auto instructions = scene_ptr_->find_game_objects_with_tag("instruction", true);
        for (auto instruction_ptr : instructions)
        {
            instruction_ptr->set_active(false);
        }
    }

    void menu_state::push_right_event()
    {
    	auto f = [this]()
    	{
    		auto direction_comp_ptr = qbert_ptr_->component<direction_component>();
    		direction_comp_ptr->set_direction(1, 1);
    		auto player_state_comp_ptr = qbert_ptr_->component<character_state_component>();
    		player_state_comp_ptr->change_state<jumping_state>(qbert_ptr_);
    	    ++jump_count_;

    	    auto instructions = scene_ptr_->find_game_objects_with_tag(std::to_string(jump_count_), true);
    	    for (auto instruction_ptr : instructions)
    	    {
    	        instruction_ptr->set_active(true);
    	    }
    	};
    	events_.emplace(f);
    }
}
