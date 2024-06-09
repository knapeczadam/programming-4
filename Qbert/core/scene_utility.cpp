#include "scene_utility.h"

// Project includes
#include "component/character/fall_component.h"
#include "component/character/jump_component.h"
#include "component/level/fly_component.h"
#include "component/npc/npc_health_component.h"
#include "component/npc/spawn_component.h"
#include "component/player/player_collider_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "component/ui/flicker_component.h"
#include "core/progress_manager.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/character/character_state.h"
#include "state/game/coop_state.h"
#include "state/player/swearing_state.h"

// Standard includes
#include <algorithm>
#include <ranges>

namespace qbert
{
    void scene_utility::freeze_all()
    {
        current_scene_.scene_ptr = current_scene();
        current_scene_.root_ptr = current_scene_.scene_ptr->find("root");
        
        current_scene_.jump_comp_ptrs            = current_scene_.root_ptr->components_in_children<jump_component>();
        current_scene_.spawn_comp_ptrs           = current_scene_.root_ptr->components_in_children<spawn_component>();
        current_scene_.fall_comp_ptrs            = current_scene_.root_ptr->components_in_children<fall_component>();
        current_scene_.flicker_comp_ptrs         = current_scene_.root_ptr->components_in_children<flicker_component>();
        current_scene_.sprite_comp_ptrs          = current_scene_.root_ptr->components_in_children<mngn::sprite_component>();
        current_scene_.sprite_ui_comp_ptrs       = current_scene_.root_ptr->components_in_children<mngn::sprite_ui_component>();
        current_scene_.player_collider_comp_ptrs = current_scene_.root_ptr->components_in_children<player_collider_component>();
        current_scene_.fly_comp_ptrs             = current_scene_.root_ptr->components_in_children<fly_component>();
        current_scene_.character_state_comp_ptrs = current_scene_.root_ptr->components_in_children<character_state_component>();

        if (game_state()->is_state<coop_state>())
        {
            for (auto const &comp_ptr : current_scene_.jump_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player"))
                {
                    comp_ptr->freeze();
                }
                else
                {
                    comp_ptr->set_enabled(false);
                }
            }

            for (auto const &comp_ptr : current_scene_.fall_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player"))
                {
                    comp_ptr->freeze();
                }
                else
                {
                    comp_ptr->set_enabled(false);
                }
            }

            for (auto const &comp_ptr : current_scene_.character_state_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player") and not comp_ptr->is_state<swearing_state>())
                {
                    comp_ptr->state<character_state>()->freeze();
                }
            }
            
            std::ranges::for_each(current_scene_.fly_comp_ptrs, [](auto comp_ptr) { comp_ptr->freeze(); });
        }
        else
        {
            std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
            std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false); });
        }
        
        std::ranges::for_each(current_scene_.spawn_comp_ptrs,           [](auto comp_ptr) { comp_ptr->set_enabled(false);  });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs,         [](auto comp_ptr) { comp_ptr->set_enabled(false);  });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs,          [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs,       [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.player_collider_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(false);  });
    }
    
    void scene_utility::unfreeze_all()
    {
        if (game_state()->is_state<coop_state>())
        {
            for (auto const &comp_ptr : current_scene_.jump_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player"))
                {
                    comp_ptr->unfreeze();
                }
                else
                {
                    comp_ptr->set_enabled(true);
                }
            }

            for (auto const &comp_ptr : current_scene_.fall_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player"))
                {
                    comp_ptr->unfreeze();
                }
                else
                {
                    comp_ptr->set_enabled(true);
                }
            }
            
            for (auto const &comp_ptr : current_scene_.character_state_comp_ptrs)
            {
                if (comp_ptr->owner()->has_tag("player") and  not comp_ptr->is_state<swearing_state>())
                {
                    comp_ptr->state<character_state>()->unfreeze();
                }
            }
            
            std::ranges::for_each(current_scene_.fly_comp_ptrs, [](auto comp_ptr) { comp_ptr->unfreeze(); });
        }
        else
        {
            std::ranges::for_each(current_scene_.jump_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
            std::ranges::for_each(current_scene_.fall_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true); });
        }
        
        std::ranges::for_each(current_scene_.spawn_comp_ptrs,           [](auto comp_ptr) { comp_ptr->set_enabled(true);  });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs,         [](auto comp_ptr) { comp_ptr->set_enabled(true);  });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs,          [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs,       [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.player_collider_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_enabled(true);  });
    }
    
    void scene_utility::freeze_animation()
    {
        current_scene_.scene_ptr = current_scene();
        current_scene_.root_ptr = current_root();
        
        current_scene_.sprite_ui_comp_ptrs = current_scene_.root_ptr->components_in_children<mngn::sprite_ui_component>();
        current_scene_.flicker_comp_ptrs   = current_scene_.root_ptr->components_in_children<flicker_component>();
        current_scene_.sprite_comp_ptrs    = current_scene_.root_ptr->components_in_children<mngn::sprite_component>();
        
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(false); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs,   [](auto comp_ptr) { comp_ptr->set_enabled(false);  });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs,    [](auto comp_ptr) { comp_ptr->set_animated(false); });
    }
    
    void scene_utility::unfreeze_animation()
    {
        std::ranges::for_each(current_scene_.sprite_ui_comp_ptrs, [](auto comp_ptr) { comp_ptr->set_animated(true); });
        std::ranges::for_each(current_scene_.flicker_comp_ptrs,   [](auto comp_ptr) { comp_ptr->set_enabled(true);  });
        std::ranges::for_each(current_scene_.sprite_comp_ptrs,    [](auto comp_ptr) { comp_ptr->set_animated(true); });
    }

    void scene_utility::freeze_npcs()
    {
        current_scene_.scene_ptr = current_scene();
        auto const npc_ptrs = current_scene()->find_game_objects_with_tag("npc");

        for (auto const &npc_ptr : npc_ptrs)
        {
            npc_ptr->component<jump_component>()->freeze();
            npc_ptr->component<spawn_component>()->freeze();
            npc_ptr->component<fall_component>()->freeze();
            npc_ptr->component<character_state_component>()->state<character_state>()->freeze();
            npc_ptr->component<mngn::collider_component>()->set_enabled(false);
        }
    }

    void scene_utility::unfreeze_npcs()
    {
        current_scene_.scene_ptr = current_scene();
        auto const npc_ptrs = current_scene()->find_game_objects_with_tag("npc");

        for (auto const &npc_ptr : npc_ptrs)
        {
            npc_ptr->component<jump_component>()->unfreeze();
            npc_ptr->component<spawn_component>()->unfreeze();
            npc_ptr->component<fall_component>()->unfreeze();
            npc_ptr->component<character_state_component>()->state<character_state>()->unfreeze();
            npc_ptr->component<mngn::collider_component>()->set_enabled(true);
        }
    }

    void scene_utility::hide_all()
    {
        auto scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto const &npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(false);
        }
        auto const player_ptrs = scene_ptr->find_game_objects_with_tag("player");
        for (auto const &player_ptr : player_ptrs)
        {
            player_ptr->set_active(false);
        }
    }

    void scene_utility::show_all()
    {
        auto const scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc", true);
        for (auto const &npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(true);
        }
        auto const player_ptrs = scene_ptr->find_game_objects_with_tag("player", true);
        for (auto const &player_ptr : player_ptrs)
        {
            player_ptr->set_active(true);
        }
    }

    void scene_utility::hide_npcs(bool ignore_coily)
    {
        auto const scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto const &npc_ptr : npc_ptrs)
        {
            if (ignore_coily and npc_ptr->has_tag("coily"))
            {
                continue;
            }
            npc_ptr->set_active(false);
        }
    }

    void scene_utility::show_npcs()
    {
        auto const scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc", true);
        for (auto const &npc_ptr : npc_ptrs)
        {
            npc_ptr->set_active(true);
        }
    }

    void scene_utility::kill_npcs(bool ignore_coily)
    {
        auto const scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc", true);
        for (auto const &npc_ptr : npc_ptrs)
        {
            if (ignore_coily and npc_ptr->has_tag("coily"))
            {
                continue;
            }
            npc_ptr->component<npc_health_component>()->take_damage(1);
        }
    }

    void scene_utility::trigger_root()
    {
        auto const root_ptr = current_root();
        root_ptr->set_active(false);
        root_ptr->set_active(true);
    }

    void scene_utility::trigger_npcs()
    {
        auto const scene_ptr = current_scene();
        auto const npc_ptrs = scene_ptr->find_game_objects_with_tag("npc");
        for (auto const &npc_ptr : npc_ptrs)
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

    auto scene_utility::game_state() const -> game_state_component *
    {
        auto const scene_ptr = mngn::scene_manager::instance().find("game_state");
        auto const game_state_go_ptr = scene_ptr->find("game_state");
        return game_state_go_ptr->component<game_state_component>();
    }
}
