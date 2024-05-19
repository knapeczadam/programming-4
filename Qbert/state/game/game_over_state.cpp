#include "game_over_state.h"

// Project includes
#include "scoreboard_state.h"
#include "component/character/jump_component.h"
#include "component/npc/spawn_component.h"
#include "component/player/fall_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    game_over_state::game_over_state(game_state_component *game_state_comp_ptr)
	    : game_state{game_state_comp_ptr}
    {
    }
	
    void game_over_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("game_over");
	    scene_ptr_->set_active(true);

        current_scene_.scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        current_scene_.root_ptr = current_scene_.scene_ptr->find("root");
        
        current_scene_.jump_comp_ptrs      = current_scene_.root_ptr->components_in_children<jump_component>();
        current_scene_.spawn_comp_ptrs     = current_scene_.root_ptr->components_in_children<spawn_component>();
        current_scene_.fall_comp_ptrs      = current_scene_.root_ptr->components_in_children<fall_component>();
        current_scene_.flicker_comp_ptrs   = current_scene_.root_ptr->components_in_children<flicker_component>();
        current_scene_.sprite_comp_ptrs    = current_scene_.root_ptr->components_in_children<mngn::sprite_component>();
        current_scene_.sprite_ui_comp_ptrs = current_scene_.root_ptr->components_in_children<mngn::sprite_ui_component>();

        std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.spawn_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
    }

    void game_over_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= game_over_time_)
        {
            accu_time_ = 0.0f;
            game_state_comp_ptr_->change_state<scoreboard_state>(game_state_comp_ptr_);
        }
    }

    void game_over_state::on_exit()
    {
        std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.spawn_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        
        current_scene_.root_ptr->set_active(false);
        current_scene_.root_ptr->set_active(true);
        current_scene_.root_ptr->find("player_1_swearing")->set_active(false);
        if (current_scene_.root_ptr->find("player_2_swearing")) current_scene_.root_ptr->find("player_2_swearing")->set_active(false);
        
        current_scene_.scene_ptr->clear_tag();
        current_scene_.scene_ptr->set_active(false);
        scene_ptr_->set_active(false);
    }
}
