#include "sound_handler.h"

// Project includes
#include "event.h"
#include "minigin/services/service_locator.h"

namespace mngn
{
    void sound_handler::run_impl(event *event_ptr)
    {
        auto event = static_cast<sound_event*>(event_ptr);
        service_locator::sound_system().play_sound(event->sound_id, event->volume);
    }
}
