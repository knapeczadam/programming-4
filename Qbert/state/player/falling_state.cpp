#include "falling_state.h"

// Project includes
#include "component/character/position_component.h"
#include "component/character/direction_component.h"
#include "component/player/fall_component.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    falling_state::falling_state(mngn::game_object *character_ptr, int row_dir, int col_dir, int row_idx, int col_idx)
        : character_state{character_ptr}
        , row_dir_{row_dir}
        , col_dir_{col_dir}
        , row_idx_{row_idx}
        , col_idx_{col_idx}
    {
    }

    void falling_state::on_enter()
    {
        character_ptr_->component<fall_component>()->fall(row_dir_, col_dir_, row_idx_, col_idx_);

        if (character_ptr_->has_tag("player"))
        {
            scene_utility::instance().freeze_animation();
            scene_utility::instance().hide_npcs();
        }
        else if (character_ptr_->has_tag("coily"))
        {
            scene_utility::instance().hide_npcs(true);
        }
    }

    void falling_state::on_exit()
    {
        if (character_ptr_->has_tag("player"))
        {
            scene_utility::instance().unfreeze_animation();
            scene_utility::instance().show_npcs();
            
            character_ptr_->set_local_position(224.0f, 84.0f);
            character_ptr_->component<position_component>()->reset();
            character_ptr_->component<direction_component>()->reset();
        }
        else if (character_ptr_->has_tag("coily"))
        {
            scene_utility::instance().show_npcs();
        }
    }
}
