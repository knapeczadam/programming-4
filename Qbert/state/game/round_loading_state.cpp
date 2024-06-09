#include "round_loading_state.h"

// Project includes
#include "component/level/cube_component.h"
#include "component/level/small_cube_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/round_counter_component.h"
#include "component/player/score_counter_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/number_component.h"
#include "core/audio_player.h"
#include "core/level_config_manager.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "state/game/input_state.h"
#include "state/game/level_loading_state.h"
#include "state/game/scoreboard_state.h"

namespace qbert
{
    round_loading_state::round_loading_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void round_loading_state::on_enter()
    {
        scene_utility::instance().freeze_all();

        scene_ptr_ = scene_utility::instance().current_scene();

        enable_cube_animations();

        // remaining disks
        auto disks = scene_ptr_->find_game_objects_with_tag("disk");
        auto disk_time = disks.size() * time_per_disk_;
        loading_time_ += disk_time;
        disk_time_ = loading_time_ - disk_time;

        audio_player::instance().play(audio::round_complete);
    }

    void round_loading_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        disappear_time_ += mngn::game_time::instance().delta_time();
        
        if (accu_time_ >= bonus_time_ and not bonus_given_)
        {
            disable_cube_animations();
            scene_utility::instance().hide_all();
            
            auto bonus_go_ptrs = scene_utility::instance().current_scene()->find_game_objects_with_tag("bonus", true);
            for (auto bonus_ptr : bonus_go_ptrs)
            {
                bonus_ptr->set_active(true);
            }
            
            auto bonus_go_ptr = scene_utility::instance().current_scene()->find_game_objects_with_tag("bonus_number").front();
            auto bonus = bonus_go_ptr->component<number_component>()->number();
            scene_utility::instance().current_scene()->find_game_objects_with_tag("player", true).front()->component<score_counter_component>()->add_score(bonus);
            bonus_given_ = true;
        }

        if (accu_time_ >= disk_time_)
        {
            if (disappear_time_ >= time_per_disk_)
            {
                auto disks = scene_ptr_->find_game_objects_with_tag("disk");
                if (not disks.empty()) disks.front()->set_active(false);
                disappear_time_ = 0.0f;

                switch (disk_count_)
                {
                case 1:
                    audio_player::instance().play(audio::disk_1_bonus);
                    break;
                case 2:
                    audio_player::instance().play(audio::disk_2_bonus);
                    break;
                case 3:
                    audio_player::instance().play(audio::disk_3_bonus);
                    break;
                case 4:
                    audio_player::instance().play(audio::disk_4_bonus);
                    break;
                }
                disk_count_++;

                scene_ptr_->find_game_objects_with_tag("player", true).front()->component<score_counter_component>()->add_score(50);
            }
        }
        
        if (accu_time_ >= loading_time_)
        {
            accu_time_ = 0.0f;
            loading_time_ = 3.0f;
            disk_time_ = 0.0f;
            disappear_time_ = 0.5f;
            disk_count_ = 1;
            
            auto &progress_manager = progress_manager::instance();
            auto game_state_comp_ptr = scene_utility::instance().game_state();

            auto root_ptr = scene_utility::instance().current_root();
            if (progress_manager.round() == 4)
            {
                root_ptr->component_in_children<level_counter_component>()->increase_level();
                if (progress_manager::instance().level() > level_config_manager::instance().level_count())
                {
                    if (score_manager::instance().is_below_lowest_score(progress_manager::instance().score()))
                    {
                        game_state_comp_ptr_->change_state<scoreboard_state>(game_state_comp_ptr_);
                    }
                    else
                    {
                        game_state_comp_ptr_->change_state<input_state>(game_state_comp_ptr_);
                    }
                    return;
                }
                root_ptr->component_in_children<round_counter_component>()->set_round(1);
                
                game_state_comp_ptr->change_state<level_loading_state>(game_state_comp_ptr);
            }
            else
            {
                root_ptr->component_in_children<round_counter_component>()->increase_round();
                game_state_comp_ptr_->load_game_mode();
            }
        }
    }

    void round_loading_state::on_exit()
    {
        scene_utility::instance().unfreeze_all();
        scene_utility::instance().trigger_root();
        
        auto bonus_go_ptr = scene_utility::instance().current_scene()->find_game_objects_with_tag("bonus");
        for (auto bonus_ptr : bonus_go_ptr)
        {
            bonus_ptr->set_active(false);
        }
        bonus_given_ = false;
        
        // Hide the current scene
        auto scene_ptr = scene_utility::instance().current_scene();
        scene_ptr->clear_tag();
        scene_ptr->set_active(false);
    }

    void round_loading_state::enable_cube_animations()
    {
        auto cube_go_ptrs = scene_ptr_->find_game_objects_with_tag("cube");
        for (auto cube_go_ptr : cube_go_ptrs)
        {
            auto cube_comp_ptr = cube_go_ptr->component<cube_component>();
            cube_comp_ptr->enable_animation();
        }
        
        scene_ptr_->find(scene_utility::instance().scene_id() + "small_cube")->component<small_cube_component>()->enable_animation();
    }

    void round_loading_state::disable_cube_animations()
    {
        auto cube_go_ptrs = scene_ptr_->find_game_objects_with_tag("cube");
        for (auto cube_go_ptr : cube_go_ptrs)
        {
            auto cube_comp_ptr = cube_go_ptr->component<cube_component>();
            cube_comp_ptr->disable_animation();
        }

        scene_ptr_->find(scene_utility::instance().scene_id() + "small_cube")->component<small_cube_component>()->disable_animation();
    }
}
