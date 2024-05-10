#include "levels.h"

// Project includes
#include "component/cube_component.h"
#include "component/health_component.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/game_object_commands.h"
#include "input/generic_commands.h"

#include "minigin/component/sprite_component.h"
#include "minigin/component/texture_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void load_test_level()
    {
        using namespace mngn;

        auto debug_command = std::make_unique<qbert::debug_command>();

        auto const scene = scene_manager::get_instance().create_scene("test_level");
        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;
        
        auto color_1 = sprite_manager::get_instance().load_sprite(qb_sp_level_1_red_cube_1, qb_re_t_sprite_general);
        auto color_2 = sprite_manager::get_instance().load_sprite(qb_sp_level_1_yellow_cube_1, qb_re_t_sprite_general);
        auto color_3 = sprite_manager::get_instance().load_sprite(qb_sp_level_1_blue_cube_1, qb_re_t_sprite_general);
        
        for (int i = 0; i < 7; ++i)
        {
            glm::vec2 start_position = origin + glm::vec2(i * offset_x, i * offset_y);
            for (int j = 0; j < i + 1; ++j)
            {
                auto go = scene->add_game_object("cube_" + std::to_string(i) + "_" + std::to_string(j));
                glm::vec2 pos = start_position + glm::vec2(j * 64, 0);
                go->set_local_position(pos);
                go->add_component<sprite_component>();
                auto cube = go->add_component<cube_component>(std::vector{color_1, color_2, color_3}, true);
                debug_command->add_observer(cube);
            }
        }
        input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, k_j, std::move(debug_command));
    }
}
