#include "service_locator.h"

// Project includes
#include "null_sound_system.h"

namespace mngn
{
    std::unique_ptr<i_sound_system> service_locator::sound_system_ = std::make_unique<null_sound_system>();
}
