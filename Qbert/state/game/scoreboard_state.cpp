#include "scoreboard_state.h"

// Project includes
#include "minigin/core/game_object.h"
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
        scene_ptr_ = mngn::scene_manager::instance().get_scene_by_name("scoreboard");
        scene_ptr_->set_active(true);
    }

    void scoreboard_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
