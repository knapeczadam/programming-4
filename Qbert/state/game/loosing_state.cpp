#include "loosing_state.h"

#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"

namespace qbert
{
    loosing_state::loosing_state(mngn::scene *scene_ptr)
        : game_state{scene_ptr}
    {
    }

    void loosing_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
