#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    class swearing_state final : public character_state
    {
    public:
        explicit swearing_state(mngn::game_object* character_ptr);

        void on_enter() override;
        void update()   override;
        void on_exit()  override;
        
    private:
        float const swear_audio_time_ = 1.0f;
        float const swear_time_       = 2.0f;
        float accu_time_swearing_     = 0.0f;
        float accu_time_audio_        = 0.0f;
        bool is_swearing_             = false;
        bool is_audio_played_         = false;
    };
}
