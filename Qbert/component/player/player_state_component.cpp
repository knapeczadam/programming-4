#include "player_state_component.h"

// Project includes
#include "state/idle_state.h"
#include "state/null_state.h"
#include "state/start_state.h"

namespace qbert
{
    player_state_component::player_state_component()
        : player_state_{std::make_unique<null_state>(owner())}
    {
    }

    player_state_component::~player_state_component() = default;

    void player_state_component::awake()
    {
        change_state<start_state>(owner());
    }

    void player_state_component::update()
    {
        player_state_->update();
    }
}
