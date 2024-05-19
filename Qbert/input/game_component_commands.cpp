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
#include "minigin/core/scene_manager.h"
#include "state/game/loading_state.h"
#include "state/game/menu_state.h"


namespace qbert
{
    damage_command::damage_command(mngn::game_component *component_ptr, int damage)
        : game_component_command{component_ptr}
        , damage_{damage}
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

    game_mode_command::game_mode_command(mngn::game_component *component_ptr, int game_mode)
        : game_component_command{component_ptr}
        , game_mode_{game_mode}
    {
    }

    void game_mode_command::execute()
    {
        auto game_state_comp_ptr = static_cast<game_state_component*>(game_component_ptr_);
        if (not game_state_comp_ptr->is_state<menu_state>()) return;
        game_state_comp_ptr->change_state<loading_state>(game_state_comp_ptr, game_mode_);
    }
}
