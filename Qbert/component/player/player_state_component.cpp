#include "player_state_component.h"

// Project includes
#include "state/null_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    player_state_component::player_state_component()
    {
        state_ = std::make_unique<null_state>();
    }

    void player_state_component::awake()
    {
        change_state<start_state>(owner());
    }

    void player_state_component::update()
    {
        state_->update();
    }
}
