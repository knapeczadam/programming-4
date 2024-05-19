#include "duo_state.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    duo_state::duo_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void duo_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().get_scene_by_name("duo");
        scene_ptr_->set_active(true);
    }

    void duo_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
