#include "level_manager_component.h"

// Project includes
#include "component/level/disc_component.h"
#include "component/player/health_component.h"
#include "component/character/jump_component.h"
#include "component/state/state_component.h"
#include "component/character/position_component.h"
#include "component/character/direction_component.h"
#include "minigin/core/game_object.h"
#include "state/player/dead_state.h"
#include "state/player/falling_state.h"
#include "state/player/flying_state.h"
#include "state/player/idle_state.h"
#include "state/player/swearing_state.h"
#include "state/player/waiting_state.h"
#include "state/game/game_over_state.h"
#include "state/npc/npc_idle_state.h"

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
            auto position_comp_ptr = static_cast<position_component*>(subject_ptr);
            auto const row_idx = position_comp_ptr->row();
            auto const cold_idx = position_comp_ptr->col();

            auto character_ptr = position_comp_ptr->owner();
            auto state_comp_ptr = character_ptr->component<state_component>();
            auto direction_comp_ptr = character_ptr->component<direction_component>();
            auto const row_dir = direction_comp_ptr->row();
            auto const col_dir = direction_comp_ptr->col();

            if (character_ptr->has_tag("player"))
            {
                for (auto const &disc_ptr : discs_)
                {
                    // player is on a disc
                    if (disc_ptr->col() == -1) // left side
                    {
                        if (row_idx + 1 == disc_ptr->row() and cold_idx == disc_ptr->col())
                        {
                            state_comp_ptr->change_state<flying_state>(character_ptr, disc_ptr);
                            return;
                        }
                    }
                    else if (row_idx + 1 == disc_ptr->row() and cold_idx + 1 == disc_ptr->col()) // right side
                    {
                        state_comp_ptr->change_state<flying_state>(character_ptr, disc_ptr);
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
            auto health_comp_ptr = static_cast<health_component*>(subject_ptr);
            auto player_ptr = health_comp_ptr->owner();
            auto position_idx_comp_ptr = player_ptr->component<position_component>();
            auto const row_idx = position_idx_comp_ptr->row();
            auto const col_idx = position_idx_comp_ptr->col();
            if (health_comp_ptr->health() == 0)
            {
                player_ptr->component<state_component>()->change_state<dead_state>(player_ptr);

                // auto game_state_comp_ptr = owner()->component<state_component>();
                // game_state_comp_ptr->change_state<game_over_state>(game_state_comp_ptr->scene());
            }
            else if (row_idx < 0 or col_idx < 0 or col_idx > row_idx or row_idx >= 7)
            {
                player_ptr->component<state_component>()->change_state<waiting_state>(player_ptr, 1.0f);
            }
            else if (health_comp_ptr->health() != 3)
            {
                player_ptr->component<state_component>()->change_state<swearing_state>(player_ptr);
            }
        }
    }
}
