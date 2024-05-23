#include "single_state.h"

// Project includes
#include "core/progress_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    single_state::single_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void single_state::on_enter()
    {
        auto level = std::to_string(progress_manager::instance().level());
        auto round = std::to_string(progress_manager::instance().round());
        scene_ptr_ = mngn::scene_manager::instance().find("single_" + level + "_" + round);
        scene_ptr_->set_tag("current");
        scene_ptr_->set_active(true);
    }
}
