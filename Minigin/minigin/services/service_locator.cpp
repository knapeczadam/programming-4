#include "service_locator.h"

// Project includes
#include "minigin/services/null_sound_system.h"

namespace mngn
{
    std::unique_ptr<sound_system> service_locator::sound_system_ = std::make_unique<null_sound_system>();
}
