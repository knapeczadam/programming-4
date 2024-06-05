#include "services.h"

// Project includes
#include "minigin/service/logging_sound_system.h"
#include "minigin/service/sdl_sound_system.h"
#include "minigin/service/service_locator.h"

namespace qbert
{
    void register_services()
    {
#ifndef NDEBUG
	mngn::service_locator::register_sound_system(std::make_unique<mngn::logging_sound_system>(std::make_unique<mngn::sdl_sound_system>()));
#else
	mngn::service_locator::register_sound_system(std::make_unique<mngn::sdl_sound_system>());
#endif
    }
}
