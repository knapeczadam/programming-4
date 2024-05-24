#include "level_manager_component.h"

// Project includes
#include "cube_component.h"
#include "component/character/direction_component.h"
#include "component/character/jump_component.h"
#include "component/character/position_component.h"
#include "component/level/disk_component.h"
#include "component/character/health_component.h"
#include "component/state/character_state_component.h"
#include "component/state/game_state_component.h"
#include "core/progress_manager.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/level_loading_state.h"
#include "state/game/round_loading_state.h"
#include "state/npc/npc_dead_state.h"
#include "state/npc/npc_idle_state.h"
#include "state/player/dead_state.h"
#include "state/player/falling_state.h"
#include "state/player/flying_state.h"
#include "state/player/idle_state.h"
#include "state/player/swearing_state.h"
#include "state/player/waiting_state.h"

// Standard includes
#include <iostream>
#include <string>

#include "state/player/jumping_state.h"
#include "state/player/start_state.h"

namespace qbert
{
    void level_manager_component::awake()
    {
        disks_ = owner()->components_in_children<disk_component>();
    }

    void level_manager_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "position_changed")
        {
            auto position_comp_ptr = static_cast<position_component*>(subject_ptr);
            auto const row_idx = position_comp_ptr->row();
            auto const cold_idx = position_comp_ptr->col();

            auto character_ptr = position_comp_ptr->owner();
            auto state_comp_ptr = character_ptr->component<character_state_component>();
            auto direction_comp_ptr = character_ptr->component<direction_component>();
            auto const row_dir = direction_comp_ptr->row();
            auto const col_dir = direction_comp_ptr->col();

            if (character_ptr->has_tag("player"))
            {
                for (auto const &disk_ptr : disks_)
                {
                    // player is on a disk
                    // left side
                    if (disk_ptr->col() == -1)
                    {
                        if (row_idx + 1 == disk_ptr->row() and cold_idx == disk_ptr->col())
                        {
                            auto pos = disk_ptr->owner()->local_position();
                            auto new_pos = glm::vec2{pos} + glm::vec2{4.0f, -14.0f};
                            disk_ptr->owner()->set_local_position(new_pos);
                            state_comp_ptr->change_state<flying_state>(character_ptr, disk_ptr);
                            return;
                        }
                    }
                    // right side
                    else if (row_idx + 1 == disk_ptr->row() and cold_idx + 1 == disk_ptr->col())
                    {
                        auto pos = disk_ptr->owner()->local_position();
                        auto new_pos = glm::vec2{pos} + glm::vec2{-2.0f, -14.0f};
                        disk_ptr->owner()->set_local_position(new_pos);
                        state_comp_ptr->change_state<flying_state>(character_ptr, disk_ptr);
                        return;
                    }
                }
            }

            // character is falling
            if (row_idx < 0 or cold_idx < 0 or cold_idx > row_idx or row_idx >= 7)
            {
                state_comp_ptr->change_state<falling_state>(character_ptr, row_dir, col_dir, row_idx, cold_idx);
                return;
            }

            // character is idle
            if (character_ptr->has_tag("player"))
            {
                state_comp_ptr->change_state<idle_state>(character_ptr);
            }
            else if (character_ptr->has_tag("npc"))
            {
                state_comp_ptr->change_state<npc_idle_state>(character_ptr);
            }
        }

        if (event == "health_changed")
        {
            auto health_comp_ptr = dynamic_cast<health_component*>(subject_ptr);
            auto character_ptr = health_comp_ptr->owner();
            auto position_idx_comp_ptr = character_ptr->component<position_component>();
            auto const row_idx = position_idx_comp_ptr->row();
            auto const col_idx = position_idx_comp_ptr->col();

            if (health_comp_ptr->health() < 0)
            {
                std::cout << "Health is negative" << '\n';
            }
            
            if (character_ptr->has_tag("player"))
            {
                // player is dead
                if (character_ptr->component<character_state_component>()->is_state<falling_state>() and health_comp_ptr->health() == 0)
                {
                    character_ptr->component<character_state_component>()->change_state<dead_state>(character_ptr);
                }
                // player is falling
                else if (row_idx < 0 or col_idx < 0 or col_idx > row_idx or row_idx >= 7)
                {
                    character_ptr->component<character_state_component>()->change_state<start_state>(character_ptr);
                }
                // player is colliding
                else if (health_comp_ptr->health() != 3)
                {
                    character_ptr->component<character_state_component>()->change_state<swearing_state>(character_ptr);
                }
            }
            // npc is dead
            else if (character_ptr->has_tag("npc") and health_comp_ptr->health() == 0)
            {
                character_ptr->component<character_state_component>()->change_state<npc_dead_state>(character_ptr);
            }
        }

        if (event == "color_changed")
        {
            auto cube_comp_ptr = static_cast<cube_component*>(subject_ptr);
            auto &progress_manager = progress_manager::instance();
            progress_manager.set_cube(cube_comp_ptr->owner()->name(), cube_comp_ptr->has_final_color());
            if (progress_manager.round_completed())
            {
                auto scene_ptr = mngn::scene_manager::instance().find("game_state");
                auto game_state_go_ptr = scene_ptr->find("game_state");
                auto game_state_comp_ptr = game_state_go_ptr->component<game_state_component>();
                
                game_state_comp_ptr->change_state<round_loading_state>(game_state_comp_ptr);
            }
        }
    }
}
