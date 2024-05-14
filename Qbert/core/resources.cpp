#include "resources.h"

// Project includes
#include "minigin/core/resource_manager.h"

namespace qbert
{
    void init_resources()
    {
		using namespace mngn;
    	resource_manager::instance()
    		.set_resource_config_path("configs/resource_config.json")
    		.load_resource_config();

    	resource_manager::instance()
    		.add_resource_pair(qb_re_t_sprite_general, "t_sprite_general")
    		.add_resource_pair(qb_re_t_sprite_large_text, "t_sprite_large_text")
    		.add_resource_pair(qb_re_t_debug, "t_debug")
    	
    		.add_resource_pair(qb_re_e_qbert_fall, "e_qbert_fall")
    		.add_resource_pair(qb_re_e_qbert_jump, "e_qbert_jump")
    	
    		.add_resource_pair(qb_re_s_level_screen, "s_level_screen");
    }
}
