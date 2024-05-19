#include "game_state_component.h"

// Project includes
#include "state/game/menu_state.h"

namespace qbert
{
    game_state_component::game_state_component()
    {
        change_state<menu_state>(this);
    }
}
