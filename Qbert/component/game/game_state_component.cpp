#include "game_state_component.h"

// Project includes
#include "state/null_state.h"
#include "state/game/playing_state.h"

namespace qbert
{

    game_state_component::game_state_component(mngn::scene *scene_ptr)
        : scene_ptr_{scene_ptr}
    {
        state_ = std::make_unique<null_state>();
    }

    void game_state_component::awake()
    {
        change_state<playing_state>(scene_ptr_);
    }

    void game_state_component::update()
    {
        
    }
}
