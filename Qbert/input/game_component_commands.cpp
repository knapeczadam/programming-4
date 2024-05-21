#include "game_component_commands.h"

#include "component/player/health_component.h"
#include "component/player/score_counter_component.h"
#include "core/resources.h"
#include "minigin/core/resource_manager.h"
#include "minigin/events/event.h"
#include "minigin/events/event_manager.h"
#include "minigin/events/sound_handler.h"

// Standard includes
#include <iostream>
#include <thread>

#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/game_over_state.h"
#include "state/game/loading_state.h"
#include "state/game/menu_state.h"


namespace qbert
{
    damage_command::damage_command(mngn::game_component *component_ptr, int dir)
        : game_component_command{component_ptr}
        , damage_{dir}
    {
    }

    void damage_command::execute()
    {
        static_cast<health_component*>(game_component_ptr_)->take_damage(damage_);

        // Play test sound - temporary
        auto event = std::make_unique<mngn::sound_event>();
        event->sound_id = qb_re_e_qbert_fall;
        event->volume = 100;
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sound handler" << '\n';
        mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(std::move(event));
    }

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

        auto scene_ptr = mngn::scene_manager::instance().find("menu");
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
        game_state_comp_ptr->change_state<loading_state>(game_state_comp_ptr);
    }
}
