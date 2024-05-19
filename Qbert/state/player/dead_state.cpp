#include "dead_state.h"

#include "component/state/game_state_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/game_over_state.h"

namespace qbert
{
    dead_state::dead_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void dead_state::on_enter()
    {
        auto scene_ptr = mngn::scene_manager::instance().find("game_state");
        auto go_ptr = scene_ptr->find("game_state");
        go_ptr->component<game_state_component>()->change_state<game_over_state>(go_ptr->component<game_state_component>());
    }
}
