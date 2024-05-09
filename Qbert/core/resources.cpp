#include "resources.h"

// Project includes
#include "minigin/core/resource_manager.h"

namespace qbert
{
    void init_resources()
    {
		using namespace mngn;
    	resource_manager::get_instance()
    		.set_resource_config_path("configs/resource_config.json")
    		.load_resource_config();

    	resource_manager::get_instance()
    		.add_resource_pair(qb_re_t_background, "t_background")
    		.add_resource_pair(qb_re_t_pacman, "t_pacman")
    		.add_resource_pair(qb_re_t_ghost, "t_ghost")
    		.add_resource_pair(qb_re_t_sprite_atlas, "t_sprite_atlas")
    		.add_resource_pair(qb_re_e_qbert_fall, "e_qbert_fall")
    		.add_resource_pair(qb_re_e_qbert_jump, "e_qbert_jump")
    		.add_resource_pair(qb_re_s_level_screen, "s_level_screen");
    }
}
