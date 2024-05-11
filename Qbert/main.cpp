// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "component/move_component.h"
#include "component/player/health_component.h"
#include "component/player/level_component.h"
#include "component/player/round_component.h"
#include "component/player/score_component.h"
#include "component/ui/health_display_component.h"
#include "component/ui/level_display_component.h"
#include "component/ui/round_display_component.h"
#include "component/ui/score_display_component.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "input/game_component_commands.h"
#include "input/game_object_commands.h"
#include "input/generic_commands.h"
#include "level/levels.h"
#include "ui/ui.h"

#include "minigin/component/debug/fps_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/component/rendering/texture_component.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/engine.h"
#include "minigin/core/game_object.h"
#include "minigin/core/resource_manager.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"
#include "minigin/services/logging_sound_system.h"
#include "minigin/services/sdl_sound_system.h"
#include "minigin/services/service_locator.h"
#include "minigin/test/test_manager.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <cassert>

// SDL includes
#include <SDL.h>

void register_services()
{
#ifndef _NDEBUG
	mngn::service_locator::register_sound_system(std::make_unique<mngn::logging_sound_system>(std::make_unique<mngn::sdl_sound_system>()));
#else
	dae::service_locator::register_sound_system(std::make_unique<dae::sdl_sound_system>());
#endif
}

void load()
{
    using namespace mngn;
	using namespace qbert;

	register_services();
	
	init_resources();
	init_sprites();
	
	load_test_level();
	load_test_ui();

    auto const scene = scene_manager::get_instance().create_scene("Demo");
    
    // Fonts
    auto const font_small = resource_manager::get_instance().load_font("fonts/Lingua.otf", 10);

    // FPS
    auto go = scene->add_game_object();
    go->set_local_position(10.0f, 500.0f);
    auto const fps_comp = go->add_component<fps_component>();
    fps_comp->set_font(font_small);
    fps_comp->set_text("FPS: ");
	
	go = scene->add_game_object("score_1");
	go->set_local_position(32, 48);
	go->add_component<multisprite_ui_component>();
	auto score_display_comp = go->add_component<score_display_component>();
        
	go = scene->add_game_object("qbert_life_1");
	go->set_local_position(16, 160);
	go->add_component<multisprite_ui_component>(multisprite_orientation::vertical);
	auto health_display_comp = go->add_component<health_display_component>();
	
	go = scene->add_game_object("numbers_level");
	go->set_local_position(432, 80);
	go->add_component<sprite_ui_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general, false);
	auto level_display_comp_ptr = go->add_component<level_display_component>();

	go = scene->add_game_object("numbers_round");
	go->set_local_position(432, 96);
	go->add_component<sprite_ui_component>(qb_sp_numbers_regular_orange, qb_re_t_sprite_general, false);
	auto round_display_comp_ptr = go->add_component<round_display_component>();

	go = scene->add_game_object("player");
	auto level_comp_ptr = go->add_component<level_component>();
	level_comp_ptr->add_observer(level_display_comp_ptr);
	auto round_comp_ptr = go->add_component<round_component>();
	round_comp_ptr->add_observer(round_display_comp_ptr);

	//---------------------------------------------------------------------------------
	// DEBUG
	//---------------------------------------------------------------------------------
	auto debug_command_ptr = std::make_unique<debug_command>(round_comp_ptr);
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, k_j, std::move(debug_command_ptr));
	
    //---------------------------------------------------------------------------------
    // PLAYER 1
    //---------------------------------------------------------------------------------
    go = scene->add_game_object("player_1");
    go->set_local_position(100.0f, 50.0f);
    go->add_component<sprite_component>(qb_sp_qbert_1, qb_re_t_sprite_general);
	go->add_component<move_component>();
    auto health_comp = go->add_component<health_component>();
    // health_comp->add_observer();
    auto score_comp = go->add_component<score_component>();
    // score_comp->add_observer(score_display_comp);

    // Arrow keys
    auto move_left_command1  = std::make_unique<move_command>(go, glm::vec2{-1, 0});
    auto move_right_command1 = std::make_unique<move_command>(go, glm::vec2{1, 0});
    auto move_up_command1    = std::make_unique<move_command>(go, glm::vec2{0, -1});
    auto move_down_command1  = std::make_unique<move_command>(go, glm::vec2{0, 1});

	auto reset_move_command_pacman = std::make_unique<reset_move_command>(go);

    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_left, std::move(move_left_command1));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_right, std::move(move_right_command1));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_up, std::move(move_up_command1));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_down, std::move(move_down_command1));

	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_left, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_right, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_up, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_down, reset_move_command_pacman->clone());

    // Controller
    auto move_left_command3  = std::make_unique<move_command>(go, glm::vec2{-1, 0});
    auto move_right_command3 = std::make_unique<move_command>(go, glm::vec2{1, 0});
    auto move_up_command3    = std::make_unique<move_command>(go, glm::vec2{0, -1});
    auto move_down_command3  = std::make_unique<move_command>(go, glm::vec2{0, 1});
    
    input_manager::get_instance().bind_command(input_type::controller, input_state::pressed, input::c_left, std::move(move_left_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::pressed, input::c_right, std::move(move_right_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::pressed, input::c_up, std::move(move_up_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::pressed, input::c_down, std::move(move_down_command3));

	input_manager::get_instance().bind_command(input_type::controller, input_state::up, input::c_left, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::controller, input_state::up, input::c_right, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::controller, input_state::up, input::c_up, reset_move_command_pacman->clone());
	input_manager::get_instance().bind_command(input_type::controller, input_state::up, input::c_down, reset_move_command_pacman->clone());
    
    // Damage
    auto damage_command1 = std::make_unique<damage_command>(health_comp);
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_x, std::move(damage_command1));
    
    // Scores
    auto score_command1 = std::make_unique<score_command>(score_comp, 10);
    auto score_command2 = std::make_unique<score_command>(score_comp, 100);
    
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_a, std::move(score_command1));
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_b, std::move(score_command2));

    //---------------------------------------------------------------------------------
    // PLAYER 2
    //---------------------------------------------------------------------------------
    go = scene->add_game_object("player_2");
    go->set_local_position(50.0f, 50.0f);
    go->add_component<sprite_component>(qb_sp_qbert_2, qb_re_t_sprite_general);
	go->add_component<move_component>();
    health_comp = go->add_component<health_component>();
    health_comp->add_observer(health_display_comp);
    score_comp = go->add_component<score_component>();
    score_comp->add_observer(score_display_comp);
    
    // WASD
    auto move_left_command2  = std::make_unique<move_command>(go, glm::vec2{-1, 0});
    auto move_right_command2 = std::make_unique<move_command>(go, glm::vec2{1, 0});
    auto move_up_command2    = std::make_unique<move_command>(go, glm::vec2{0, -1});
    auto move_down_command2  = std::make_unique<move_command>(go, glm::vec2{0, 1});

	auto reset_move_command_ghost = std::make_unique<reset_move_command>(go);
    
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_a, std::move(move_left_command2));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_d, std::move(move_right_command2));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_w, std::move(move_up_command2));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_s, std::move(move_down_command2));

	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_a, reset_move_command_ghost->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_d, reset_move_command_ghost->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_w, reset_move_command_ghost->clone());
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::up, input::k_s, reset_move_command_ghost->clone());

    // Damage
    auto damage_command2 = std::make_unique<damage_command>(health_comp);
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_c, std::move(damage_command2));

    // Scores
    auto score_command3 = std::make_unique<score_command>(score_comp, 10);
    auto score_command4 = std::make_unique<score_command>(score_comp, 100);
    
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_z, std::move(score_command3));
    input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_x, std::move(score_command4));

}

int main(int, char *[])
{
    mngn::engine engine("../Data/");
	
#ifndef NDEBUG
    mngn::test_manager::get_instance().run_all_tests();
#endif
	
    engine.run(load);
	
    return 0;
}
