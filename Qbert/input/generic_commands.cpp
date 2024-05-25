﻿#include "generic_commands.h"

// Project includes
#include "component/state/game_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/sound/sound_manager.h"
#include "state/game/coop_state.h"
#include "state/game/round_loading_state.h"
#include "state/game/single_state.h"
#include "state/game/versus_state.h"

// Standard includes
#include <iostream>
#include <thread>

#include "core/resources.h"
#include "minigin/events/event.h"
#include "minigin/events/event_manager.h"
#include "minigin/events/sound_handler.h"

namespace qbert
{
    debug_command::debug_command(void *debug_ptr)
        : debug_ptr_(debug_ptr)
    {
    }

    void debug_command::execute()
    {
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sound handler" << '\n';
        mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_lift));
    }

    void toggle_mute_command::execute()
    {
        mngn::sound_manager::instance().toggle_mute();
        std::cout << "Volume is " << mngn::sound_manager::instance().volume()  << '\n';
    }

    void skip_round_command::execute()
    {
        auto scene_ptr = mngn::scene_manager::instance().find("game_state");
        auto game_state_go_ptr = scene_ptr->find("game_state");
        auto game_state_comp_ptr = game_state_go_ptr->component<game_state_component>();
        if (game_state_comp_ptr->is_state<single_state>() or game_state_comp_ptr->is_state<coop_state>() or game_state_comp_ptr->is_state<versus_state>())
        {
            game_state_comp_ptr->change_state<round_loading_state>(game_state_comp_ptr);
        }
        
    }
}
