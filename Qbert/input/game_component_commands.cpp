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


namespace qbert
{
    void damage_command::execute()
    {
        static_cast<health_component*>(game_component())->take_damage(damage_);

        // Play test sound - temporary
        auto event = std::make_unique<mngn::sound_event>();
        event->sound_id = qb_re_e_qbert_fall;
        event->volume = 100;
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sound handler" << '\n';
        mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(std::move(event));
    }
}
