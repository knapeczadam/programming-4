// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "Achievement.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "GameActorCommand.h"
#include "HealthComponent.h"
#include "HealthTextComponent.h"
#include "InputManager.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ScoreTextComponent.h"
#include "TestManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"

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

    const auto scene = SceneManager::GetInstance().CreateScene("Demo");
    
    // Fonts
    const auto fontMedium = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
    const auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

    // Background
    auto go = scene->AddGameObject();
    go->AddComponent<TextureComponent>("background.tga");

    // Text
    go = scene->AddGameObject();
    go->SetLocalPosition(180.0f, 10.0f);
    auto textComp = go->AddComponent<TextComponent>();
    textComp->SetFont(fontMedium);
    textComp->SetText("Programming 4 Assignment");

    // FPS
    go = scene->AddGameObject();
    go->SetLocalPosition(10.0f, 10.0f);
    const auto fpsComp = go->AddComponent<FPSComponent>();
    fpsComp->SetFont(fontMedium);
    fpsComp->SetText("FPS: ");
    
    //---------------------------------------------------------------------------------
    // UI
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject("hint");
    go->SetLocalPosition(10, 80);
    textComp = go->AddComponent<TextComponent>();
    textComp->SetFont(fontSmall);
    textComp->SetText("Use the D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets\n"
                      "Use WASD to move GHOST, C to inflict damage, Z and X to pick up pellets");

    std::stringstream healthSS;
    healthSS << "# lives: " << HealthComponent::GetInitialHealth();

    std::stringstream scoreSS;
    scoreSS << "Score: " << ScoreComponent::GetInitialScore();

    go = scene->AddGameObject("pacman_health");
    go->SetLocalPosition(10, 120);
    const auto pacmanHealthText = go->AddComponent<HealthTextComponent>();
    pacmanHealthText->SetFont(fontSmall);
    pacmanHealthText->SetText(healthSS.str());

    go = scene->AddGameObject("pacman_score");
    go->SetLocalPosition(10, 140);
    const auto pacmanScoreText = go->AddComponent<ScoreTextComponent>();
    pacmanScoreText->SetFont(fontSmall);
    pacmanScoreText->SetText(scoreSS.str());
    
    go = scene->AddGameObject("ghost_health");
    go->SetLocalPosition(10, 160);
    const auto ghostHealthText = go->AddComponent<HealthTextComponent>();
    ghostHealthText->SetFont(fontSmall);
    ghostHealthText->SetText(healthSS.str());
    
    go = scene->AddGameObject("ghost_score");
    go->SetLocalPosition(10, 180);
    const auto ghostScoreText = go->AddComponent<ScoreTextComponent>();
    ghostScoreText->SetFont(fontSmall);
    ghostScoreText->SetText(scoreSS.str());
    
    //---------------------------------------------------------------------------------
    // PACMAN
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject("pacman");
    go->SetLocalPosition(200.0f, 200.0f);
    go->AddComponent<TextureComponent>("pacman.tga");
    auto healthComp = go->AddComponent<HealthComponent>();
    healthComp->AddObserver(pacmanHealthText);
    auto scoreComp = go->AddComponent<ScoreComponent>();
    scoreComp->AddObserver(pacmanScoreText);

    // Arrow keys
    auto moveLeftCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand1 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand1    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_LEFT, std::move(moveLeftCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_RIGHT, std::move(moveRightCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_UP, std::move(moveUpCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_DOWN, std::move(moveDownCommand1));

    // Controller
    auto moveLeftCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand3 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand3    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Pressed, Input::C_LEFT, std::move(moveLeftCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Pressed, Input::C_RIGHT, std::move(moveRightCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Pressed, Input::C_UP, std::move(moveUpCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Pressed, Input::C_DOWN, std::move(moveDownCommand3));
    
    // Damage
    auto damageCommand1 = std::make_unique<DamageCommand>(healthComp);
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_X, std::move(damageCommand1));
    
    // Scores
    auto scoreCommand1 = std::make_unique<ScoreCommand>(scoreComp, 10);
    auto scoreCommand2 = std::make_unique<ScoreCommand>(scoreComp, 100);
    
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_A, std::move(scoreCommand1));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_B, std::move(scoreCommand2));

    //---------------------------------------------------------------------------------
    // GHOST
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject("ghost");
    go->SetLocalPosition(300.0f, 300.0f);
    go->AddComponent<TextureComponent>("ghost.tga");
    healthComp = go->AddComponent<HealthComponent>();
    healthComp->AddObserver(ghostHealthText);
    scoreComp = go->AddComponent<ScoreComponent>();
    scoreComp->AddObserver(ghostScoreText);
    
    // WASD
    auto moveLeftCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand2 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand2    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_a, std::move(moveLeftCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_d, std::move(moveRightCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_w, std::move(moveUpCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_s, std::move(moveDownCommand2));

    // Damage
    auto damageCommand2 = std::make_unique<DamageCommand>(healthComp);
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_c, std::move(damageCommand2));

    // Scores
    auto scoreCommand3 = std::make_unique<ScoreCommand>(scoreComp, 10);
    auto scoreCommand4 = std::make_unique<ScoreCommand>(scoreComp, 100);
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_z, std::move(scoreCommand3));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_x, std::move(scoreCommand4));

	// Reset Achievements
	auto resetAchievementsCommand = std::make_unique<ResetAchievementsCommand>(g_SteamAchievements);
	InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_r, std::move(resetAchievementsCommand));
}

int main(int, char*[])
{
    using namespace dae;

	// ------------------------
	// Steam - Initialize
	// ------------------------
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	std::cout << "Successfully initialized steam." << '\n';
	g_SteamAchievements = new CSteamAchievements(g_Achievements, 1);

	// ------------------------
	// Minigin
	// ------------------------
    Minigin engine("../Data/");
	
#if defined(_DAE_DEBUG)
    TestManager::GetInstance().RunAllTests();
#endif
	
    engine.Run(load);

	// ------------------------
	// Steam - Cleanup
	// ------------------------
    SteamAPI_Shutdown();
    // Delete the SteamAchievements object
	delete g_SteamAchievements;
	
    return 0;
}
