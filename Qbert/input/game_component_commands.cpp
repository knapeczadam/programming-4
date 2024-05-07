#include "game_component_commands.h"

#include "engine/resource_manager.h"
#include "component/health_component.h"
#include "component/score_component.h"
#include "engine/events/event.h"
#include "engine/events/event_manager.h"
#include "engine/events/sound_handler.h"

// Standard includes
#include <iostream>
#include <thread>


namespace dae
{
    void damage_command::execute()
    {
        static_cast<health_component*>(get_game_component())->take_damage(damage_);

        // Play test sound - temporary
        auto event = std::make_unique<sound_event>();
        event->sound_id = resource_id::e_qbert_jump;
        event->volume = 100;
        std::cout << "# Thread " << std::this_thread::get_id() << " : calling sound handler" << '\n';
        event_manager::get_instance().get_handler<sound_handler>()->add_event(std::move(event));
    }

    void score_command::execute()
    {
        // basically its just broadcasting a function, simpler way to call a function
        static_cast<score_component*>(get_game_component())->add_score(score_);
    }
}
