#include "player_state_component.h"

// Project includes
#include "state/idle_state.h"
#include "state/null_state.h"
#include "state/start_state.h"

namespace qbert
{
    player_state_component::player_state_component()
        : player_state_{std::make_unique<null_state>(get_owner())}
    {
    }

    player_state_component::~player_state_component() = default;

    void player_state_component::awake()
    {
        change_state(std::make_unique<start_state>(get_owner()));
    }

    void player_state_component::update()
    {
        player_state_->update();
    }

    void player_state_component::change_state(std::unique_ptr<player_state> new_state)
    {
        player_state_->on_exit();
        player_state_ = std::move(new_state);
        player_state_->on_enter();
    }
}
