#include "game_over_state.h"

#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"

namespace qbert
{
    game_over_state::game_over_state(mngn::scene *scene_ptr)
        : game_state{scene_ptr}
    {
    }

    void game_over_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
