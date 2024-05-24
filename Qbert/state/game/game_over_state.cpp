#include "game_over_state.h"

// Project includes
#include "component/state/game_state_component.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/input_state.h"
#include "state/game/scoreboard_state.h"

namespace qbert
{
    game_over_state::game_over_state(game_state_component *game_state_comp_ptr)
	    : game_state{game_state_comp_ptr}
    {
    }
	
    void game_over_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("game_over");
	    scene_ptr_->set_active(true);

        scene_utility::instance().freeze_animation();
        scene_utility::instance().hide_all();
    }

    void game_over_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= game_over_time_)
        {
            accu_time_ = 0.0f;
            
            if (score_manager::instance().is_below_lowest_score(progress_manager::instance().score()))
            {
                game_state_comp_ptr_->change_state<scoreboard_state>(game_state_comp_ptr_);
            }
            else
            {
                game_state_comp_ptr_->change_state<input_state>(game_state_comp_ptr_);
            }
        }
    }

    void game_over_state::on_exit()
    {
        scene_utility::instance().unfreeze_animation();
        scene_utility::instance().trigger_root();

        auto scene_ptr = scene_utility::instance().current_scene();
        scene_ptr->set_active(false);
        scene_ptr->clear_tag();
        
        scene_ptr_->set_active(false);
    }
}
