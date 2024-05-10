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
        qb_re_e_qbert_fall,
        qb_re_e_qbert_jump,

        // --- Streams ---
        qb_re_s_level_screen
    };
    
    void init_resources();
}
