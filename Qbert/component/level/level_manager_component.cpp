#include "level_manager_component.h"

// Project includes
#include "component/game/game_state_component.h"
#include "component/level/disc_component.h"
#include "component/player/health_component.h"
#include "component/player/jump_component.h"
#include "component/player/player_state_component.h"
#include "component/player/player_position_component.h"
#include "component/direction_component.h"
#include "minigin/core/game_object.h"
#include "state/player/dead_state.h"
#include "state/player/falling_state.h"
#include "state/player/flying_state.h"
#include "state/player/idle_state.h"
#include "state/player/swearing_state.h"
#include "state/player/waiting_state.h"
#include "state/game/game_over_state.h"

namespace qbert
{
    void level_manager_component::awake()
    {
        discs_ = owner()->components_in_children<disc_component>();
    }

    void level_manager_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "position_changed")
        {
            auto position_comp_ptr = dynamic_cast<player_position_component*>(subject_ptr);
            auto const row_idx = position_comp_ptr->row();
            auto const cold_idx = position_comp_ptr->col();

            auto player_ptr = position_comp_ptr->owner();
            auto player_state_comp_ptr = player_ptr->component<player_state_component>();
            auto direction_comp_ptr = player_ptr->component<direction_component>();
            auto const row_dir = direction_comp_ptr->row();
            auto const col_dir = direction_comp_ptr->col();
            
            for (auto const &disc_ptr : discs_)
            {
                // player is on a disc
                if (disc_ptr->col() == -1) // left side
                {
                    if (row_idx + 1 == disc_ptr->row() and cold_idx == disc_ptr->col())
                    {
                        player_state_comp_ptr->change_state<flying_state>(player_ptr, disc_ptr);
                        return;
                    }
                }
                else if (row_idx + 1 == disc_ptr->row() and cold_idx + 1 == disc_ptr->col()) // right side
                {
                    player_state_comp_ptr->change_state<flying_state>(player_ptr, disc_ptr);
                    return;
                }
            }

            // player is falling
            if (row_idx < 0 or cold_idx < 0 or cold_idx > row_idx or row_idx >= 7)
            {
                player_state_comp_ptr->change_state<falling_state>(player_ptr, row_dir, col_dir, row_idx, cold_idx);
                return;
            }

            // player is idle
            player_state_comp_ptr->change_state<idle_state>(player_ptr);
        }

        if (event == "health_changed")
        {
            auto health_comp_ptr = dynamic_cast<health_component*>(subject_ptr);
            auto player_ptr = health_comp_ptr->owner();
            auto position_idx_comp_ptr = player_ptr->component<player_position_component>();
            auto const row_idx = position_idx_comp_ptr->row();
            auto const col_idx = position_idx_comp_ptr->col();
            if (health_comp_ptr->health() == 0)
            {
                player_ptr->component<player_state_component>()->change_state<dead_state>(player_ptr);

                auto game_state_comp_ptr = owner()->component<game_state_component>();
                game_state_comp_ptr->change_state<game_over_state>(game_state_comp_ptr->scene());
            }
            else if (row_idx < 0 or col_idx < 0 or col_idx > row_idx or row_idx >= 7)
            {
                player_ptr->component<player_state_component>()->change_state<waiting_state>(player_ptr, 1.0f);
            }
            else if (health_comp_ptr->health() != 3)
            {
                player_ptr->component<player_state_component>()->change_state<swearing_state>(player_ptr);
            }
        }
    }

}
