#pragma once

// Project includes
#include "i_sound_system.h"
#include "null_sound_system.h"

// Standard includes
#include <memory>


namespace mngn
{
    class service_locator
    {
    public:
        static void register_sound_system(std::unique_ptr<i_sound_system> &&sound_system)
        {
            sound_system_ = std::move(sound_system);
        }

        static auto get_sound_system() -> i_sound_system & { return *sound_system_; }

    private:
        static std::unique_ptr<i_sound_system> sound_system_;
    };
}
