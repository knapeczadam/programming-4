#pragma once

namespace qbert
{
    enum qbert_resource
    {
        // --- Textures ---
        qb_re_t_sprite_general,
        qb_re_t_sprite_large_text,
        qb_re_t_debug,

        // --- Effects ---
        qb_re_e_ball_jump,
        qb_re_e_coily_egg_jump,
        qb_re_e_coily_fall,
        qb_re_e_coily_jump,
        qb_re_e_coin,
        qb_re_e_disk_lift,
        qb_re_e_prize,
        qb_re_e_qbert_fall,
        qb_re_e_qbert_jump,
        qb_re_e_qbert_swearing_1,
        qb_re_e_qbert_swearing_2,
        qb_re_e_ugg,

        // --- Streams ---
        qb_re_s_bye,
        qb_re_s_extra_time,
        qb_re_s_hello,
        qb_re_s_level_1,
        qb_re_s_level_2,
        qb_re_s_level_3,
        qb_re_s_round_complete
    };
    
    void register_resources();
}
