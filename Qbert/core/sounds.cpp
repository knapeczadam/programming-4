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
            .register_effect(qb_re_e_ball_jump)
            .register_effect(qb_re_e_coily_egg_jump)
            .register_effect(qb_re_e_coily_fall)
            .register_effect(qb_re_e_coily_jump)
            .register_effect(qb_re_e_coin)
            .register_effect(qb_re_e_disk_lift)
            .register_effect(qb_re_e_prize)
            .register_effect(qb_re_e_qbert_fall)
            .register_effect(qb_re_e_qbert_jump)
            .register_effect(qb_re_e_qbert_swearing_1)
            .register_effect(qb_re_e_qbert_swearing_2)
            .register_effect(qb_re_e_ugg)
        
            .register_stream(qb_re_s_level_start)
            .register_stream(qb_re_s_round_complete);
    }
}
