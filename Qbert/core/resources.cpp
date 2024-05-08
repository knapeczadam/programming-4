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
    		.add_resource_pair(to_int(resource::e_qbert_fall), "e_qbert_fall")
    		.add_resource_pair(to_int(resource::e_qbert_jump), "e_qbert_jump")
    		.add_resource_pair(to_int(resource::s_01_credit), "s_01_credit");
    }

    auto to_int(resource id) -> int
    {
    	return static_cast<int>(id);
    }
}
