﻿#include "coop_state.h"

// Project includes
#include "core/progress_manager.h"
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
        auto const level = std::to_string(progress_manager::instance().level());
        auto const round = std::to_string(progress_manager::instance().round());
        scene_ptr_ = mngn::scene_manager::instance().find("coop_" + level + "_" + round);
        scene_ptr_->set_tag("current");
        scene_ptr_->set_active(true);
    }
}
