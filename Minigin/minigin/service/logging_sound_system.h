#pragma once

// Project includes
#include "minigin/service/sound_system.h"

// Standard includes
#include <memory>

namespace mngn
{
    class logging_sound_system final : public sound_system
    {
    public:
        explicit logging_sound_system(std::unique_ptr<sound_system> &&sound_system) : sound_system_{std::move(sound_system)} {}

    protected:
        void play_sound_impl(int id, int volume) override;

    private:
        std::unique_ptr<sound_system> sound_system_;
    };
}
