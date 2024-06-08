#include "sounds.h"

// Project includes
#include "core/resources.h"
#include "minigin/sound/sound_manager.h"

namespace qbert
{
    void register_sounds()
    {
        using namespace mngn;
        sound_manager::instance()
            .register_effect(qb_re_e_ball_bump)
            .register_effect(qb_re_e_ball_jump)
            .register_effect(qb_re_e_bonus)
            .register_effect(qb_re_e_coily_bump)
            .register_effect(qb_re_e_coily_egg_jump)
            .register_effect(qb_re_e_coily_fall)
            .register_effect(qb_re_e_coily_jump)
            .register_effect(qb_re_e_coin)
            .register_effect(qb_re_e_disk_1_bonus)
            .register_effect(qb_re_e_disk_2_bonus)
            .register_effect(qb_re_e_disk_3_bonus)
            .register_effect(qb_re_e_disk_4_bonus)
            .register_effect(qb_re_e_disk_lift)
            .register_effect(qb_re_e_initial_end)
            .register_effect(qb_re_e_qbert_fall)
            .register_effect(qb_re_e_qbert_jump)
            .register_effect(qb_re_e_qbert_swearing_1)
            .register_effect(qb_re_e_qbert_swearing_2)
            .register_effect(qb_re_e_qbert_swearing_3)
            .register_effect(qb_re_e_ugg)
        
            .register_stream(qb_re_s_bye)
            .register_stream(qb_re_s_extra_time)
            .register_stream(qb_re_s_hello)
            .register_stream(qb_re_s_level_1)
            .register_stream(qb_re_s_level_2)
            .register_stream(qb_re_s_level_3)
            .register_stream(qb_re_s_round_complete);
    }
}
