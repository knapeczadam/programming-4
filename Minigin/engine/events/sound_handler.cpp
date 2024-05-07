#include "sound_handler.h"

// Project includes
#include "event.h"
#include "service_locator.h"

namespace dae
{
    void sound_handler::run_impl(event *event_ptr)
    {
        auto event = static_cast<sound_event*>(event_ptr);
        service_locator::get_sound_system().play_sound(event->sound_id, event->volume);
    }
}
