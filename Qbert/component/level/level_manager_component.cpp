﻿#include "level_manager_component.h"

// Project includes
#include "component/level/disc_component.h"
#include "component/player/jump_component.h"
#include "component/player/player_state_component.h"
#include "component/player/position_idx_component.h"
#include "minigin/core/game_object.h"
#include "state/falling_state.h"
#include "state/flying_state.h"
#include "state/idle_state.h"

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
            auto position_comp_ptr = dynamic_cast<position_idx_component*>(subject_ptr);
            auto const row_idx = position_comp_ptr->row_idx();
            auto const cold_idx = position_comp_ptr->col_idx();

            auto player_ptr = position_comp_ptr->owner();
            auto player_state_comp_ptr = player_ptr->component<player_state_component>();
            auto jump_comp_ptr = player_ptr->component<jump_component>();
            auto const row_dir = jump_comp_ptr->row_direction();
            auto const col_dir = jump_comp_ptr->col_direction();
            
            for (auto const &disc_ptr : discs_)
            {
                // player is on a disc
                if (disc_ptr->col_idx() == -1) // left side
                {
                    if (row_idx + 1 == disc_ptr->row_idx() and cold_idx == disc_ptr->col_idx())
                    {
                        player_state_comp_ptr->change_state<flying_state>(player_ptr, disc_ptr);
                        return;
                    }
                }
                else if (row_idx + 1 == disc_ptr->row_idx() and cold_idx + 1 == disc_ptr->col_idx()) // right side
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
    }
}
