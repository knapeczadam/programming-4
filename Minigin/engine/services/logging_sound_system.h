#pragma once

// Project includes
#include "i_sound_system.h"

// Standard includes
#include <memory>

namespace dae
{
    class logging_sound_system final : public i_sound_system
    {
    public:
        ~logging_sound_system() override = default;
        
        explicit logging_sound_system(std::unique_ptr<i_sound_system> &&sound_system) : sound_system_{std::move(sound_system)} {}
        
        void play_sound(sound_id const id, float const volume) const override;

    private:
        std::unique_ptr<i_sound_system> sound_system_;
    };
}
