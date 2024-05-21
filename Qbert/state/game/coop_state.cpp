#include "coop_state.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    coop_state::coop_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void coop_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("coop");
        scene_ptr_->set_tag("current");
        scene_ptr_->set_active(true);
    }
}
