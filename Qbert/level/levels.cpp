#include "levels.h"

// Project includes
#include "component/level/cube_component.h"
#include "component/player/health_component.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/game_object_commands.h"
#include "input/generic_commands.h"

#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/rendering/texture_component.h"
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

        auto const scene = scene_manager::instance().create_scene("test_level");
        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;
        
        auto color_1 = sprite_manager::instance().load_sprite(qb_sp_level_1_red_cube_1, qb_re_t_sprite_general);
        auto color_2 = sprite_manager::instance().load_sprite(qb_sp_level_1_yellow_cube_1, qb_re_t_sprite_general);
        auto color_3 = sprite_manager::instance().load_sprite(qb_sp_level_1_blue_cube_1, qb_re_t_sprite_general);
        
        for (int i = 0; i < 7; ++i)
        {
            glm::vec2 start_position = origin + glm::vec2(i * offset_x, i * offset_y);
            for (int j = 0; j < i + 1; ++j)
            {
                auto go = scene->add_game_object("cube_" + std::to_string(i) + "_" + std::to_string(j));
                glm::vec2 pos = start_position + glm::vec2(j * 64, 0);
                go->set_local_position(pos);
                go->add_component<sprite_component>();
                go->add_component<cube_component>(i, j, std::vector{color_1, color_2, color_3}, true);
            }
        }
    }
}
