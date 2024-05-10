#include "ui.h"

// Project includes
#include "core/resources.h"
#include "core/sprites.h"

#include "minigin/component/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"

namespace qbert
{
    void load_test_ui()
    {
        using namespace mngn;

        auto const scene = scene_manager::get_instance().create_scene("test_ui");

        auto go = scene->add_game_object("text_player_1");
        go->set_local_position(32, 32);
        go->add_component<sprite_component>(qb_sp_text_purple_player, qb_re_t_sprite_general);

        go = scene->add_game_object("text_1");
        go->set_local_position(144, 16);
        go->add_component<sprite_component>(qb_sp_text_one, qb_re_t_sprite_general);
        
        go = scene->add_game_object("score_1");
        go->set_local_position(32, 48);
        go->add_component<sprite_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general);
        
        go = scene->add_game_object("text_change_to");
        go->set_local_position(32, 80);
        go->add_component<sprite_component>(qb_sp_text_change_to, qb_re_t_sprite_general);

        go = scene->add_game_object("right_arrow_1");
        go->set_local_position(32, 96);
        go->add_component<sprite_component>(qb_sp_arrow_right, qb_re_t_sprite_general);
        
        go = scene->add_game_object("right_arrow_1");
        go->set_local_position(48, 96);
        go->add_component<sprite_component>(qb_sp_arrow_right, qb_re_t_sprite_general);
        
        go = scene->add_game_object("small_cube");
        go->set_local_position(64, 96);
        go->add_component<sprite_component>(qb_sp_level_1_red_cube_small, qb_re_t_sprite_general);
        
        go = scene->add_game_object("left_arrow_1");
        go->set_local_position(96, 96);
        go->add_component<sprite_component>(qb_sp_arrow_left, qb_re_t_sprite_general);
        
        go = scene->add_game_object("left_arrow_2");
        go->set_local_position(112, 96);
        go->add_component<sprite_component>(qb_sp_arrow_left, qb_re_t_sprite_general);
        
        go = scene->add_game_object("text_level");
        go->set_local_position(368, 80);
        go->add_component<sprite_component>(qb_sp_text_level, qb_re_t_sprite_general);
        
        go = scene->add_game_object("numbers_level");
        go->set_local_position(432, 80);
        go->add_component<sprite_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general);
        
        go = scene->add_game_object("text_round");
        go->set_local_position(368, 96);
        go->add_component<sprite_component>(qb_sp_text_round, qb_re_t_sprite_general);
        
        go = scene->add_game_object("numbers_round");
        go->set_local_position(432, 96);
        go->add_component<sprite_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general);
        
        go = scene->add_game_object("qbert_life_1");
        go->set_local_position(16, 160);
        go->add_component<sprite_component>(qb_sp_qbert_life, qb_re_t_sprite_general);
        
        go = scene->add_game_object("qbert_life_2");
        go->set_local_position(16, 192);
        go->add_component<sprite_component>(qb_sp_qbert_life, qb_re_t_sprite_general);
        
        go = scene->add_game_object("qbert_life_3");
        go->set_local_position(16, 224);
        go->add_component<sprite_component>(qb_sp_qbert_life, qb_re_t_sprite_general);
    }
}
