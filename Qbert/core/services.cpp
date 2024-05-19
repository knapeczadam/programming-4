#include "services.h"

// Project includes
#include "minigin/services/logging_sound_system.h"
#include "minigin/services/sdl_sound_system.h"
#include "minigin/services/service_locator.h"

namespace qbert
{
    void register_services()
    {
#ifndef _NDEBUG
	mngn::service_locator::register_sound_system(std::make_unique<mngn::logging_sound_system>(std::make_unique<mngn::sdl_sound_system>()));
#else
	dae::service_locator::register_sound_system(std::make_unique<dae::sdl_sound_system>());
#endif
    }
}
