#include "ui.h"

// Project includes
#include "component/ui/flicker_component.h"
#include "core/resources.h"
#include "core/sprites.h"

#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void load_test_ui()
    {
        using namespace mngn;

        auto const scene = scene_manager::instance().create_scene("test_ui");

        auto go = scene->add_game_object("text_player_1");
        go->set_local_position(32, 32);
        go->add_component<sprite_ui_component>(qb_sp_text_purple_player, qb_re_t_sprite_general);

        go = scene->add_game_object("text_1");
        go->set_local_position(144, 16);
        go->add_component<sprite_ui_component>(qb_sp_text_one, qb_re_t_sprite_general);
        
        
        go = scene->add_game_object("text_change_to");
        go->set_local_position(32, 80);
        go->add_component<sprite_ui_component>(qb_sp_text_change_to, qb_re_t_sprite_general);

        go = scene->add_game_object("right_arrow_1");
        go->set_local_position(32, 96);
        go->add_component<flicker_component>();
        go->add_component<sprite_ui_component>(qb_sp_arrow_right, qb_re_t_sprite_general);
        
        go = scene->add_game_object("right_arrow_1");
        go->set_local_position(48, 96);
        go->add_component<flicker_component>(0.2f);
        go->add_component<sprite_ui_component>(qb_sp_arrow_right, qb_re_t_sprite_general);
        
        go = scene->add_game_object("small_cube");
        go->set_local_position(64, 96);
        go->add_component<sprite_ui_component>(qb_sp_level_1_red_cube_small, qb_re_t_sprite_general);
        
        go = scene->add_game_object("left_arrow_1");
        go->set_local_position(96, 96);
        go->add_component<flicker_component>(0.2f);
        go->add_component<sprite_ui_component>(qb_sp_arrow_left, qb_re_t_sprite_general);
        
        go = scene->add_game_object("left_arrow_2");
        go->set_local_position(112, 96);
        go->add_component<flicker_component>();
        go->add_component<sprite_ui_component>(qb_sp_arrow_left, qb_re_t_sprite_general);
        
        go = scene->add_game_object("text_level");
        go->set_local_position(368, 80);
        go->add_component<sprite_ui_component>(qb_sp_text_level, qb_re_t_sprite_general);
        
        go = scene->add_game_object("text_round");
        go->set_local_position(368, 96);
        go->add_component<sprite_ui_component>(qb_sp_text_round, qb_re_t_sprite_general);
        
    }
}
