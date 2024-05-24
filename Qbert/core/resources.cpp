﻿#include "resources.h"

// Project includes
#include "minigin/core/resource_manager.h"

namespace qbert
{
    void register_resources()
    {
		using namespace mngn;
    	resource_manager::instance()
    		.set_resource_config_path("configs/resource_config.json")
    		.load_resource_config();

    	resource_manager::instance()
    		.register_resource(qb_re_t_sprite_general, "t_sprite_general")
    		.register_resource(qb_re_t_sprite_large_text, "t_sprite_large_text")
    		.register_resource(qb_re_t_debug, "t_debug")
    	
    		.register_resource(qb_re_e_ball_jump, "e_ball_jump")
    		.register_resource(qb_re_e_coily_egg_jump, "e_coily_egg_jump") 
    		.register_resource(qb_re_e_coily_fall, "e_coily_fall") 
    		.register_resource(qb_re_e_coily_jump, "e_coily_jump") 
    		.register_resource(qb_re_e_coin, "e_coin") 
    		.register_resource(qb_re_e_disk_lift, "e_disk_lift") 
    		.register_resource(qb_re_e_prize, "e_prize") 
    		.register_resource(qb_re_e_qbert_fall, "e_qbert_fall") 
    		.register_resource(qb_re_e_qbert_jump, "e_qbert_jump") 
    		.register_resource(qb_re_e_qbert_swearing_1, "e_qbert_swearing_1") 
    		.register_resource(qb_re_e_qbert_swearing_2, "e_qbert_swearing_2") 
    		.register_resource(qb_re_e_ugg, "e_ugg")
    	
    		.register_resource(qb_re_s_level_start, "s_level_start") 
    		.register_resource(qb_re_s_round_complete, "s_round_complete"); 
    }
}
