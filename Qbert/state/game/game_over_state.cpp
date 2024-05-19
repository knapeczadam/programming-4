#include "game_over_state.h"

// Project includes
#include "scoreboard_state.h"
#include "component/state/game_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

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
    }

    void game_over_state::update()
    {
        
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= game_over_time_)
        {
            accu_time_ = 0.0f;
            game_state_comp_ptr_->change_state<scoreboard_state>(game_state_comp_ptr_);
        }
    }

    void game_over_state::on_exit()
    {
        auto scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        scene_ptr->clear_tag();
        scene_ptr->set_active(false);
        
        scene_ptr_->set_active(false);
    }
}
