#include "menu_state.h"

// Project includes
#include <iostream>

#include "minigin/core/game_object.h"
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
    }

    void menu_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
