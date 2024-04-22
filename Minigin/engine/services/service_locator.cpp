#include "service_locator.h"

namespace dae
{
    std::unique_ptr<i_sound_system> service_locator::sound_system_ = nullptr;
}
