#include "dead_state.h"

#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/null_state.h"
#include "state/game/game_over_state.h"

namespace qbert
{
    dead_state::dead_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void dead_state::on_enter()
    {
        auto game_state_comp_ptr = scene_utility::instance().game_state();
        game_state_comp_ptr->change_state<game_over_state>(game_state_comp_ptr);

        scene_utility::instance().freeze_all();
        character_ptr_->component<character_state_component>()->change_state<null_state>();
    }

    void dead_state::on_exit()
    {
        scene_utility::instance().unfreeze_all();
    }
}
