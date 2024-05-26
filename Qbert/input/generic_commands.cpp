#include "generic_commands.h"

// Project includes
#include "component/state/game_state_component.h"
#include "component/ui/number_component.h"
#include "core/audio_player.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/sound/sound_manager.h"
#include "state/game/coop_state.h"
#include "state/game/menu_state.h"
#include "state/game/round_loading_state.h"
#include "state/game/single_state.h"
#include "state/game/versus_state.h"

// Standard includes
#include <iostream>
#include <thread>

namespace qbert
{
    debug_command::debug_command(void *debug_ptr)
        : debug_ptr_(debug_ptr)
    {
    }

    void debug_command::execute()
    {
        std::cout << '#' << std::this_thread::get_id() << " thread: calling sound handler" << '\n';
        audio_player::instance().play(audio::disk_4_bonus);
    }

    void toggle_mute_command::execute()
    {
        mngn::sound_manager::instance().toggle_mute();
        std::cout << "Volume is " << mngn::sound_manager::instance().volume()  << '\n';
    }

    void skip_round_command::execute()
    {
        auto game_state_comp_ptr = scene_utility::instance().game_state();
        if (game_state_comp_ptr->is_state<single_state>() or game_state_comp_ptr->is_state<coop_state>() or game_state_comp_ptr->is_state<versus_state>())
        {
            game_state_comp_ptr->change_state<round_loading_state>(game_state_comp_ptr);
        }
    }

    void insert_coin_command::execute()
    {
        auto game_state_comp_ptr = scene_utility::instance().game_state();
        if (game_state_comp_ptr->is_state<menu_state>())
        {
            auto number_comp_ptrs = scene_utility::instance().current_scene()->find_game_objects_with_tag("coin");
            auto number_comp_ptr = number_comp_ptrs.front()->component<number_component>();
            progress_manager::instance().add_coin();
            number_comp_ptr->set_number(progress_manager::instance().coins());

            audio_player::instance().play(audio::coin);
        }
    }
}
