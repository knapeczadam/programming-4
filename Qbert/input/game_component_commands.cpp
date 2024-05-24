#include "game_component_commands.h"

#include "component/character/health_component.h"
#include "component/player/score_counter_component.h"
#include "core/resources.h"
#include "minigin/core/resource_manager.h"
#include "minigin/events/event.h"
#include "minigin/events/event_manager.h"
#include "minigin/events/sound_handler.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/initial_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/game_over_state.h"
#include "state/game/input_state.h"
#include "state/game/level_loading_state.h"
#include "state/game/menu_state.h"

// Standard includes
#include <iostream>
#include <thread>

namespace qbert
{
    game_mode_select_command::game_mode_select_command(mngn::game_component *component_ptr, int game_mode)
        : game_component_command{component_ptr}
        , dir_{game_mode}
    {
    }

    void game_mode_select_command::execute()
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        if (not game_state_comp_ptr->is_state<menu_state>()) return;
        game_state_comp_ptr->set_game_mode(dir_);

        update_underline("menu_1");
        update_underline("menu_2");
    }

    void game_mode_select_command::update_underline(std::string const &scene_name)
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        
        auto scene_ptr = mngn::scene_manager::instance().find(scene_name);
        auto active_ptr = scene_ptr->find_game_objects_with_tag("active").front();
        active_ptr->remove_tag("active");
        active_ptr->set_active(false);
        
        switch (game_state_comp_ptr->game_mode())
        {
        case 0:
            scene_ptr->find("underline_single", true)->add_tag("active");
            break;
        case 1:
            scene_ptr->find("underline_coop", true)->add_tag("active");
            break;
        case 2:
            scene_ptr->find("underline_versus", true)->add_tag("active");
            break;
        }
        scene_ptr->find_game_objects_with_tag("active", true).front()->set_active(true);
    }

    game_mode_accept_command::game_mode_accept_command(mngn::game_component *component_ptr)
        : game_component_command{component_ptr}
    {
    }

    void game_mode_accept_command::execute()
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        if (not game_state_comp_ptr->is_state<menu_state>()) return;
        game_state_comp_ptr->change_state<level_loading_state>(game_state_comp_ptr);
    }

    input_select_command::input_select_command(mngn::game_component *component_ptr, int dir)
        : game_component_command{component_ptr}
        , dir_{dir}
    {
    }

    void input_select_command::execute()
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        if (not game_state_comp_ptr->is_state<input_state>()) return;
        initial_manager::instance().move_input(dir_);
    }

    input_accept_command::input_accept_command(mngn::game_component *component_ptr)
        : game_component_command{component_ptr}
    {
    }

    void input_accept_command::execute()
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        if (not game_state_comp_ptr->is_state<input_state>()) return;
        initial_manager::instance().accept_input();
    }
}
