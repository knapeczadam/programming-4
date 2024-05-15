#include "playing_state.h"

#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"

namespace qbert
{
    playing_state::playing_state(mngn::scene *scene_ptr)
        : game_state{scene_ptr}
    {
    }

    void playing_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
