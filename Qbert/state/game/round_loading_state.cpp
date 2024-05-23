#include "round_loading_state.h"

// Project includes
#include "component/state/game_state_component.h"
#include "minigin/core/game_time.h"
#include "input_state.h"
#include "level_loading_state.h"
#include "scoreboard_state.h"
#include "component/character/jump_component.h"
#include "component/npc/spawn_component.h"
#include "component/player/fall_component.h"
#include "component/player/level_counter_component.h"
#include "component/player/round_counter_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/progress_manager.h"
#include "core/score_manager.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
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
        current_scene_.scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        current_scene_.root_ptr = current_scene_.scene_ptr->find("root");
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
            
            if (progress_manager.round() == 4)
            {
                current_scene_.root_ptr->component_in_children<level_counter_component>()->increase_level();
                current_scene_.root_ptr->component_in_children<round_counter_component>()->set_round(1);
                
                game_state_comp_ptr->change_state<level_loading_state>(game_state_comp_ptr);
            }
            else
            {
                current_scene_.root_ptr->component_in_children<round_counter_component>()->increase_round();
                game_state_comp_ptr_->load_game_mode();
            }
        }
    }

    void round_loading_state::on_exit()
    {
        // Trigger on_enable to reset the components
        current_scene_.root_ptr->set_active(false);
        current_scene_.root_ptr->set_active(true);
        
        // Hide the current scene
        current_scene_.scene_ptr->clear_tag();
        current_scene_.scene_ptr->set_active(false);
    }
}
