#include "audio_player.h"

// Project includes
#include "resources.h"
#include "minigin/events/event.h"
#include "minigin/events/event_manager.h"
#include "minigin/events/sound_handler.h"

namespace qbert
{
    void audio_player::play(music id)
    {
        switch (id)
        {
        case music::ball_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_ball_jump));
            break;
        case music::coily_egg_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_egg_jump));
            break;
        case music::coily_fall:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_fall));
            break;
        case music::coily_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coily_jump));
            break;
        case music::coin:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_coin));
            break;
        case music::disk_lift:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_disk_lift));
            break;
        case music::prize:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_prize));
            break;
        case music::qbert_fall:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_fall));
            break;
        case music::qbert_jump:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_jump));
            break;
        case music::qbert_swearing_1:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_swearing_1));
            break;
        case music::qbert_swearing_2:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_qbert_swearing_2));
            break;
        case music::ugg:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_e_ugg));
            break;
        case music::bye:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_bye));
            break;
        case music::extra_time:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_extra_time));
            break;
        case music::hello:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_hello));
            break;
        case music::level_1:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_1));
            break;
        case music::level_2:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_2));
            break;
        case music::level_3:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_level_3));
            break;
        case music::round_complete:
            mngn::event_manager::instance().handler<mngn::sound_handler>()->add_event(mngn::event::create_event<mngn::sound_event>(qb_re_s_round_complete));
            break;
        }
    }
}
