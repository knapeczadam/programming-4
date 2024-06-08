#include "audio_player.h"

// Project includes
#include "resources.h"
#include "minigin/service/service_locator.h"
#include "minigin/service/sound_system.h"

namespace qbert
{
    void audio_player::play(audio id, int volume)
    {
        switch (id)
        {
        case audio::ball_bump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_ball_bump, volume);
            break;
        case audio::ball_jump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_ball_jump, volume);
            break;
        case audio::bonus:
            mngn::service_locator::sound_system().play_sound(qb_re_e_bonus, volume);
            break;
        case audio::coily_bump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_coily_bump, volume);
            break;
        case audio::coily_egg_jump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_coily_egg_jump, volume);
            break;
        case audio::coily_fall:
            mngn::service_locator::sound_system().play_sound(qb_re_e_coily_fall, volume);
            break;
        case audio::coily_jump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_coily_jump, volume);
            break;
        case audio::coin:
            mngn::service_locator::sound_system().play_sound(qb_re_e_coin, volume);
            break;
        case audio::disk_1_bonus:
            mngn::service_locator::sound_system().play_sound(qb_re_e_disk_1_bonus, volume);
            break;
        case audio::disk_2_bonus:
            mngn::service_locator::sound_system().play_sound(qb_re_e_disk_2_bonus, volume);
            break;
        case audio::disk_3_bonus:
            mngn::service_locator::sound_system().play_sound(qb_re_e_disk_3_bonus, volume);
            break;
        case audio::disk_4_bonus:
            mngn::service_locator::sound_system().play_sound(qb_re_e_disk_4_bonus, volume);
            break;
        case audio::disk_lift:
            mngn::service_locator::sound_system().play_sound(qb_re_e_disk_lift, volume);
            break;
        case audio::initial_end:
            mngn::service_locator::sound_system().play_sound(qb_re_e_initial_end, volume);
            break;
        case audio::qbert_fall:
            mngn::service_locator::sound_system().play_sound(qb_re_e_qbert_fall, volume);
            break;
        case audio::qbert_jump:
            mngn::service_locator::sound_system().play_sound(qb_re_e_qbert_jump, volume);
            break;
        case audio::qbert_swearing_1:
            mngn::service_locator::sound_system().play_sound(qb_re_e_qbert_swearing_1, volume);
            break;
        case audio::qbert_swearing_2:
            mngn::service_locator::sound_system().play_sound(qb_re_e_qbert_swearing_2, volume);
            break;
        case audio::qbert_swearing_3:
            mngn::service_locator::sound_system().play_sound(qb_re_e_qbert_swearing_3, volume);
            break;
        case audio::ugg:
            mngn::service_locator::sound_system().play_sound(qb_re_e_ugg, volume);
            break;
        case audio::bye:
            mngn::service_locator::sound_system().play_sound(qb_re_s_bye, volume);
            break;
        case audio::extra_time:
            mngn::service_locator::sound_system().play_sound(qb_re_s_extra_time, volume);
            break;
        case audio::hello:
            mngn::service_locator::sound_system().play_sound(qb_re_s_hello, volume);
            break;
        case audio::level_1:
            mngn::service_locator::sound_system().play_sound(qb_re_s_level_1, volume);
            break;
        case audio::level_2:
            mngn::service_locator::sound_system().play_sound(qb_re_s_level_2, volume);
            break;
        case audio::level_3:
            mngn::service_locator::sound_system().play_sound(qb_re_s_level_3, volume);
            break;
        case audio::round_complete:
            mngn::service_locator::sound_system().play_sound(qb_re_s_round_complete, volume);
            break;
        }
    }
}
