#include "scoreboard_state.h"

// Project includes
#include "menu_state.h"
#include "component/state/game_state_component.h"
#include "core/scene_loader.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    scoreboard_state::scoreboard_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void scoreboard_state::on_enter()
    {
        scene_loader::instance().load_scoreboard();
        scene_ptr_ = mngn::scene_manager::instance().find("scoreboard");
        scene_ptr_->set_active(true);
    }

    void scoreboard_state::update()
    {

        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= scoreboard_time_)
        {
            accu_time_ = 0.0f;
            game_state_comp_ptr_->change_state<menu_state>(game_state_comp_ptr_);
        }
    }

    void scoreboard_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
