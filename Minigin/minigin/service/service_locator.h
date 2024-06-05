#pragma once

// Project includes
#include "minigin/service/sound_system.h"

// Standard includes
#include <memory>

namespace mngn
{
    class service_locator final
    {
    public:
        static void register_sound_system(std::unique_ptr<sound_system> &&sound_system)
        {
            sound_system_ = std::move(sound_system);
        }

        static auto sound_system() -> sound_system & { return *sound_system_; }

    private:
        static std::unique_ptr<mngn::sound_system> sound_system_;
    };
}
