#include "audio_player.h"

// Project includes
#include "resources.h"
#include "minigin/events/event.h"
#include "minigin/events/event_manager.h"
#include "minigin/events/sound_handler.h"

namespace qbert
{
    void audio_player::play(audio id)
    {
        switch (id)
        {
        case audio::ball_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_ball_jump));
            break;
        case audio::bonus:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_bonus));
            break;
        case audio::coily_egg_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_egg_jump));
            break;
        case audio::coily_fall:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_fall));
            break;
        case audio::coily_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_jump));
            break;
        case audio::coin:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coin));
            break;
        case audio::disk_1_bonus:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_1_bonus));
            break;
        case audio::disk_2_bonus:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_2_bonus));
            break;
        case audio::disk_3_bonus:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_3_bonus));
            break;
        case audio::disk_4_bonus:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_4_bonus));
            break;
        case audio::disk_lift:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_lift));
            break;
        case audio::qbert_fall:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_fall));
            break;
        case audio::qbert_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_jump));
            break;
        case audio::qbert_swearing_1:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_swearing_1));
            break;
        case audio::qbert_swearing_2:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_swearing_2));
            break;
        case audio::ugg:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_ugg));
            break;
        case audio::bye:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_bye));
            break;
        case audio::extra_time:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_extra_time));
            break;
        case audio::hello:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_hello));
            break;
        case audio::level_1:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_1));
            break;
        case audio::level_2:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_2));
            break;
        case audio::level_3:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_3));
            break;
        case audio::round_complete:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_round_complete));
            break;
        }
    }
}
