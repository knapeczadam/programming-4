﻿#include "menu_state.h"

// Project includes
#include <iostream>

#include "core/progress_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    menu_state::menu_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void menu_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("menu");
        scene_ptr_->set_active(true);

        mngn::renderer::instance().set_background_color({49, 32, 115, 0});
    }

    void menu_state::on_exit()
    {
        progress_manager::instance().reset();
        scene_ptr_->set_active(false);
    }
}
