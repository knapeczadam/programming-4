#include "round_loading_state.h"

// Project includes
#include "input_state.h"
#include "level_loading_state.h"
#include "component/level/cube_component.h"
#include "component/level/small_cube_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/round_counter_component.h"
#include "component/state/game_state_component.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    round_loading_state::round_loading_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void round_loading_state::on_enter()
    {
        scene_utility::instance().freeze_all();

        auto scene_ptr = scene_utility::instance().current_scene();
        auto cube_go_ptrs = scene_ptr->find_game_objects_with_tag("cube");
        for (auto cube_go_ptr : cube_go_ptrs)
        {
            auto cube_comp_ptr = cube_go_ptr->component<cube_component>();
            cube_comp_ptr->enable_animation();
        }
        scene_ptr->find(scene_utility::instance().scene_id() + "small_cube")->component<small_cube_component>()->enable_animation();
    }

    void round_loading_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= loading_time_)
        {
            accu_time_ = 0.0f;
            
            auto &progress_manager = progress_manager::instance();
            auto scene_ptr = mngn::scene_manager::instance().find("game_state");
            auto game_state_go_ptr = scene_ptr->find("game_state");
            auto game_state_comp_ptr = game_state_go_ptr->component<game_state_component>();

            auto root_ptr = scene_utility::instance().current_root();
            if (progress_manager.round() == 4)
            {
                root_ptr->component_in_children<level_counter_component>()->increase_level();
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
        
        // Hide the current scene
        auto scene_ptr = scene_utility::instance().current_scene();
        scene_ptr->clear_tag();
        scene_ptr->set_active(false);
    }
}
