#include "scene_utility.h"

// Project includes
#include "component/character/jump_component.h"
#include "component/npc/spawn_component.h"
#include "component/player/fall_component.h"
#include "component/player/player_collider_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/progress_manager.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

// Standard includes
#include <algorithm>
#include <ranges>

namespace qbert
{
    void scene_utility::freeze_all()
    {
        current_scene_.scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        current_scene_.root_ptr = current_scene_.scene_ptr->find("root");
        
        current_scene_.jump_comp_ptrs      = current_scene_.root_ptr->components_in_children<jump_component>();
        current_scene_.spawn_comp_ptrs     = current_scene_.root_ptr->components_in_children<spawn_component>();
        current_scene_.fall_comp_ptrs      = current_scene_.root_ptr->components_in_children<fall_component>();
        current_scene_.flicker_comp_ptrs   = current_scene_.root_ptr->components_in_children<flicker_component>();
        current_scene_.sprite_comp_ptrs    = current_scene_.root_ptr->components_in_children<mngn::sprite_component>();
        current_scene_.sprite_ui_comp_ptrs = current_scene_.root_ptr->components_in_children<mngn::sprite_ui_component>();
        current_scene_.player_collider_comp_ptrs = current_scene_.root_ptr->components_in_children<player_collider_component>();

        std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.spawn_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.player_collider_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
    }
    
    void scene_utility::freeze_animation()
    {
        current_scene_.scene_ptr = current_scene();
        current_scene_.root_ptr = current_root();
        
        current_scene_.sprite_ui_comp_ptrs = current_scene_.root_ptr->components_in_children<mngn::sprite_ui_component>();
        current_scene_.flicker_comp_ptrs   = current_scene_.root_ptr->components_in_children<flicker_component>();
        current_scene_.sprite_comp_ptrs    = current_scene_.root_ptr->components_in_children<mngn::sprite_component>();
        
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
    }
    
    void scene_utility::unfreeze_all()
    {
        std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.spawn_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.player_collider_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
    }
    
    void scene_utility::unfreeze_animation()
    {
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
    }

    void scene_utility::hide_all()
    {
        auto scene_ptr = current_scene();
        auto npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(false);
        }
        auto player_ptrs = scene_ptr->find_game_objects_with_tag("player");
        for (auto player_ptr : player_ptrs)
        {
            player_ptr->set_active(false);
        }
    }

    void scene_utility::show_all()
    {
        auto scene_ptr = current_scene();
        auto npc_ptrs = scene_ptr->find_game_objects_with_tag("npc", true);
        for (auto npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(true);
        }
        auto player_ptrs = scene_ptr->find_game_objects_with_tag("player", true);
        for (auto player_ptr : player_ptrs)
        {
            player_ptr->set_active(true);
        }
    }

    void scene_utility::hide_npcs()
    {
        auto scene_ptr = current_scene();
        auto npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(false);
        }
    }

    void scene_utility::show_npcs()
    {
        auto scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        auto npc_ptrs = scene_ptr->find_game_objects_with_tag("npc", true);
        for (auto npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(true);
        }
    }

    void scene_utility::trigger_root()
    {
        auto root_ptr = current_root();
        root_ptr->set_active(false);
        root_ptr->set_active(true);
    }

    void scene_utility::trigger_npcs()
    {
        auto scene_ptr = current_scene();
        auto npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(false);
            npc_ptr->set_active(true);
        }
    }

    auto scene_utility::current_scene() const -> mngn::scene *
    {
        return mngn::scene_manager::instance().find_with_tag("current");
    }

    auto scene_utility::current_root() const -> mngn::game_object *
    {
        return current_scene()->find("root");
    }

    auto scene_utility::scene_id() const -> std::string
    {
        return current_scene()->name() + '_';
    }
}
