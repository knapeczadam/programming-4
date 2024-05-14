#include "factory.h"

// Project includes
#include "component/level/disc_component.h"
#include "component/level/fly_component.h"
#include "component/player/face_component.h"
#include "component/player/fall_component.h"
#include "component/player/health_component.h"
#include "component/player/jump_component.h"
#include "component/player/player_state_component.h"
#include "component/player/position_idx_component.h"
#include "component/player/score_counter_component.h"
#include "input/game_object_commands.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/input/input_manager.h"

namespace qbert
{
    auto factory::character::create_player(player_config_info const &config) -> player_info
    {
        player_info info;
        info.go_ptr = config.scene_ptr->add_game_object(config.name);
        info.go_ptr->set_parent(config.parent_go_ptr);
        info.go_ptr->set_local_position(config.local_position);
        info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<jump_component>();
        info.go_ptr->add_component<face_component>();
        info.go_ptr->add_component<player_state_component>();
        info.go_ptr->add_component<fall_component>();
        info.position_idx_comp_ptr  = info.go_ptr->add_component<position_idx_component>(config.row_idx, config.col_idx);
        info.health_comp_ptr        = info.go_ptr->add_component<health_component>();
        info.score_counter_comp_ptr = info.go_ptr->add_component<score_counter_component>();

        auto left_command = std::make_unique<jump_command>(info.go_ptr, -1, -1);
        auto right_command = std::make_unique<jump_command>(info.go_ptr, 1, 1);
        auto up_command = std::make_unique<jump_command>(info.go_ptr, -1, 0);
        auto down_command = std::make_unique<jump_command>(info.go_ptr, 1, 0);

        mngn::input_manager::instance().bind_command(config.left_command.input_type, config.left_command.input_state, config.left_command.input, std::move(left_command));
        mngn::input_manager::instance().bind_command(config.right_command.input_type, config.right_command.input_state, config.right_command.input, std::move(right_command));
        mngn::input_manager::instance().bind_command(config.up_command.input_type, config.up_command.input_state, config.up_command.input, std::move(up_command));
        mngn::input_manager::instance().bind_command(config.down_command.input_type, config.down_command.input_state, config.down_command.input, std::move(down_command));

        if (config.left_command_alt)
        {
            auto left_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, -1);
            mngn::input_manager::instance().bind_command(config.left_command_alt.value().input_type, config.left_command_alt.value().input_state, config.left_command_alt.value().input, std::move(left_command_alt));
        }
        if (config.right_command_alt)
        {
            auto right_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 1);
            mngn::input_manager::instance().bind_command(config.right_command_alt.value().input_type, config.right_command_alt.value().input_state, config.right_command_alt.value().input, std::move(right_command_alt));
        }
        if (config.up_command_alt)
        {
            auto up_command_alt = std::make_unique<jump_command>(info.go_ptr, -1, 0);
            mngn::input_manager::instance().bind_command(config.up_command_alt.value().input_type, config.up_command_alt.value().input_state, config.up_command_alt.value().input, std::move(up_command_alt));
        }
        if (config.down_command_alt)
        {
            auto down_command_alt = std::make_unique<jump_command>(info.go_ptr, 1, 0);
            mngn::input_manager::instance().bind_command(config.down_command_alt.value().input_type, config.down_command_alt.value().input_state, config.down_command_alt.value().input, std::move(down_command_alt));
        }

        return info;
    }

    auto factory::level::create_disc(disc_config_info const &config) -> disc_info
    {
        disc_info info;
        info.go_ptr = config.scene_ptr->add_game_object(config.name);
        info.go_ptr->set_parent(config.parent_go_ptr);
        info.go_ptr->add_component<mngn::sprite_component>(config.sprite_id, config.texture_id);
        info.go_ptr->add_component<disc_component>(config.row_idx, config.col_idx);
        info.go_ptr->add_component<fly_component>();

        return info;
    }
}
