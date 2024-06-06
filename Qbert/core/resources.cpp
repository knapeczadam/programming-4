#include "resources.h"

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
    	
    		.register_resource(qb_re_e_ball_bump, "e_ball_bump")
    		.register_resource(qb_re_e_ball_jump, "e_ball_jump")
    		.register_resource(qb_re_e_bonus, "e_bonus") 
    		.register_resource(qb_re_e_coily_egg_jump, "e_coily_egg_jump") 
    		.register_resource(qb_re_e_coily_fall, "e_coily_fall") 
    		.register_resource(qb_re_e_coily_jump, "e_coily_jump") 
    		.register_resource(qb_re_e_coin, "e_coin") 
    		.register_resource(qb_re_e_disk_1_bonus, "e_disk_1_bonus") 
    		.register_resource(qb_re_e_disk_2_bonus, "e_disk_2_bonus") 
    		.register_resource(qb_re_e_disk_3_bonus, "e_disk_3_bonus") 
    		.register_resource(qb_re_e_disk_4_bonus, "e_disk_4_bonus") 
    		.register_resource(qb_re_e_disk_lift, "e_disk_lift") 
    		.register_resource(qb_re_e_qbert_fall, "e_qbert_fall") 
    		.register_resource(qb_re_e_qbert_jump, "e_qbert_jump") 
    		.register_resource(qb_re_e_qbert_swearing_1, "e_qbert_swearing_1") 
    		.register_resource(qb_re_e_qbert_swearing_2, "e_qbert_swearing_2") 
    		.register_resource(qb_re_e_qbert_swearing_3, "e_qbert_swearing_3") 
    		.register_resource(qb_re_e_ugg, "e_ugg")
    	
    		.register_resource(qb_re_s_bye, "s_bye") 
    		.register_resource(qb_re_s_extra_time, "s_extra_time") 
    		.register_resource(qb_re_s_hello, "s_hello") 
    		.register_resource(qb_re_s_level_1, "s_level_1") 
    		.register_resource(qb_re_s_level_2, "s_level_2") 
    		.register_resource(qb_re_s_level_3, "s_level_3") 
    		.register_resource(qb_re_s_round_complete, "s_round_complete"); 
    }
}
