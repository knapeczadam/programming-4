#include "game_over_state.h"

// Project includes
#include "minigin/core/game_object.h"
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
        scene_ptr_ = mngn::scene_manager::instance().get_scene_by_name("game_over");
	    scene_ptr_->set_active(true);
    }

    void game_over_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
