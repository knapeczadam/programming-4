#include "input_state.h"

// Project includes
#include "scoreboard_state.h"
#include "component/state/game_state_component.h"
#include "core/initial_manager.h"
#include "core/progress_manager.h"
#include "core/scene_loader.h"
#include "core/score_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    input_state::input_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void input_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("input");
	    scene_ptr_->set_active(true);
        scene_loader::instance().load_input_message(score_manager::instance().calculate_ranking(progress_manager::instance().score()));
    }

    void input_state::update()
    {
        if (accu_time >= 1.0f)
        {
            scene_loader::instance().load_countdown(countdown_);
            countdown_--;
            accu_time = 0.0f;
        }
        accu_time += mngn::game_time::instance().delta_time();
        
        input_time_ -= mngn::game_time::instance().delta_time();
        if (input_time_ <= 0.0f)
        {
            input_time_ = original_input_time_;
            countdown_ = original_countdown_;
            initial_manager::instance().save_initial();
            game_state_comp_ptr_->change_state<scoreboard_state>(game_state_comp_ptr_);
        }
    }

    void input_state::on_exit()
    {
	    scene_ptr_->set_active(false);
    }
}
