#pragma once

// Project includes
#include "minigin/utility/singleton.h"

namespace qbert
{
    enum class audio
    {
        ball_jump,
        bonus,
        coily_egg_jump,
        coily_fall,
        coily_jump,
        coin,
        disk_1_bonus,
        disk_2_bonus,
        disk_3_bonus,
        disk_4_bonus,
        disk_lift,
        qbert_fall,
        qbert_jump,
        qbert_swearing_1,
        qbert_swearing_2,
        ugg,
        bye,
        extra_time,
        hello,
        level_1,
        level_2,
        level_3,
        round_complete
    };
    
    class audio_player final : public mngn::singleton<audio_player>
    {
    public:
        ~audio_player() override = default;

        audio_player(audio_player const &other)            = delete;
        audio_player(audio_player &&other)                 = delete;
        audio_player &operator=(audio_player const &other) = delete;
        audio_player &operator=(audio_player &&other)      = delete;

        void play(audio id, int volume = 100);

    private:
        friend class mngn::singleton<audio_player>;
        audio_player() = default;
    };
}
