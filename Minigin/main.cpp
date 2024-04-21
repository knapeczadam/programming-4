// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "component/implementation/fps_component.h"
#include "component/implementation/health_component.h"
#include "component/implementation/health_text_component.h"
#include "component/implementation/move_component.h"
#include "component/implementation/score_component.h"
#include "component/implementation/score_text_component.h"
#include "component/implementation/texture_component.h"
#include "component/implementation/text_component.h"
#include "core/game_object.h"
#include "engine/minigin.h"
#include "engine/resource_manager.h"
#include "engine/scene.h"
#include "engine/scene_manager.h"
#include "engine/input/game_component_command.h"
#include "engine/input/game_object_command.h"
#include "engine/input/generic_command.h"
#include "engine/input/input_manager.h"
#include "steam/achievement.h"
#include "test/test_manager.h"

// Standard includes
#include <cassert>
#include <iostream>
#include <sstream>

// SDL includes
#include <SDL.h>

// Steam includes
#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

void load()
{
    using namespace dae;

    auto const scene = scene_manager::get_instance().create_scene("Demo");
    
    // Fonts
    auto const font_medium = resource_manager::get_instance().load_font("Lingua.otf", 24);
    auto const font_small = resource_manager::get_instance().load_font("Lingua.otf", 16);

    // Background
    auto go = scene->add_game_object();
    go->add_component<texture_component>("background.tga");

    // Text
    go = scene->add_game_object();
    go->set_local_position(180.0f, 10.0f);
    auto text_comp = go->add_component<text_component>();
    text_comp->set_font(font_medium);
    text_comp->set_text("Programming 4 Assignment");

    // FPS
    go = scene->add_game_object();
    go->set_local_position(10.0f, 10.0f);
    auto const fps_comp = go->add_component<fps_component>();
    fps_comp->set_font(font_medium);
    fps_comp->set_text("FPS: ");
    
    //---------------------------------------------------------------------------------
    // UI
    //---------------------------------------------------------------------------------
    go = scene->add_game_object("hint");
    go->set_local_position(10, 80);
    text_comp = go->add_component<text_component>();
    text_comp->set_font(font_small);
    text_comp->set_text("Use the D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets\n"
	    "Use WASD to move GHOST, C to inflict damage, Z and X to pick up pellets");

    std::stringstream health_ss;
    health_ss << "# lives: " << health_component::get_initial_health();

    std::stringstream score_ss;
    score_ss << "Score: " << score_component::get_initial_score();

    go = scene->add_game_object("pacman_health");
    go->set_local_position(10, 120);
    auto const pacman_health_text = go->add_component<health_text_component>();
    pacman_health_text->set_font(font_small);
    pacman_health_text->set_text(health_ss.str());

    go = scene->add_game_object("pacman_score");
    go->set_local_position(10, 140);
    auto const pacman_score_text = go->add_component<score_text_component>();
    pacman_score_text->set_font(font_small);
    pacman_score_text->set_text(score_ss.str());
    
    go = scene->add_game_object("ghost_health");
    go->set_local_position(10, 160);
    auto const ghost_health_text = go->add_component<health_text_component>();
    ghost_health_text->set_font(font_small);
    ghost_health_text->set_text(health_ss.str());
    
    go = scene->add_game_object("ghost_score");
    go->set_local_position(10, 180);
    auto const ghost_score_text = go->add_component<score_text_component>();
    ghost_score_text->set_font(font_small);
    ghost_score_text->set_text(score_ss.str());
    
    //---------------------------------------------------------------------------------
    // PACMAN
    //---------------------------------------------------------------------------------
    go = scene->add_game_object("pacman");
    go->set_local_position(200.0f, 200.0f);
    go->add_component<texture_component>("pacman.tga");
	go->add_component<move_component>();
    auto health_comp = go->add_component<health_component>();
    health_comp->add_observer(pacman_health_text);
    auto score_comp = go->add_component<score_component>();
    score_comp->add_observer(pacman_score_text);
	score_comp->add_observer(g_steam_achievements_ptr);

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
    
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_left, std::move(move_left_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_right, std::move(move_right_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_up, std::move(move_up_command3));
    input_manager::get_instance().bind_command(input_type::controller, input_state::down, input::c_down, std::move(move_down_command3));

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
    // GHOST
    //---------------------------------------------------------------------------------
    go = scene->add_game_object("ghost");
    go->set_local_position(300.0f, 300.0f);
    go->add_component<texture_component>("ghost.tga");
	go->add_component<move_component>();
    health_comp = go->add_component<health_component>();
    health_comp->add_observer(ghost_health_text);
    score_comp = go->add_component<score_component>();
    score_comp->add_observer(ghost_score_text);
	score_comp->add_observer(g_steam_achievements_ptr);
    
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

	// Reset Achievements
	auto reset_achievement_command = std::make_unique<reset_achievements_command>(g_steam_achievements_ptr);
	input_manager::get_instance().bind_command(input_type::keyboard, input_state::down, input::k_r, std::move(reset_achievement_command));
}

int main(int, char *[])
{
    using namespace dae;

	// ------------------------
	// Steam - Initialize
	// ------------------------
	if (not SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << '\n';
		return 1;
	}
	std::cout << "Successfully initialized steam." << '\n';
	g_steam_achievements_ptr = new steam_achievements(g_achievements, 1);

	// ------------------------
	// Minigin
	// ------------------------
    minigin engine("../Data/");
	
#if defined(_DAE_DEBUG)
    test_manager::get_instance().run_all_tests();
#endif
	
    engine.run(load);

	// ------------------------
	// Steam - Cleanup
	// ------------------------
    SteamAPI_Shutdown();
    // Delete the SteamAchievements object
	delete g_steam_achievements_ptr;
	
    return 0;
}
