#include "game_state_component.h"

// Project includes
#include "state/game/coop_state.h"
#include "state/game/input_state.h"
#include "state/game/menu_state.h"
#include "state/game/scoreboard_state.h"
#include "state/game/single_state.h"
#include "state/game/versus_state.h"

namespace qbert
{
    game_state_component::game_state_component()
    {
        change_state<menu_state>(this);
    }

    void game_state_component::set_game_mode(int dir)
    {
        game_mode_ = (game_mode_ + dir) % 3;
        if (game_mode_ < 0)
        {
            game_mode_ = 2;
        }
    }

    void game_state_component::load_game_mode()
    {
        switch (game_mode_)
        {
        case 0:
            change_state<single_state>(this);
            break;
        case 1:
            change_state<coop_state>(this);
            break;
        case 2:
            change_state<versus_state>(this);
            break;
        }
    }
}
