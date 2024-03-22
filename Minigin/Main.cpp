// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "FPSComponent.h"
#include "GameObjectCommand.h"
#include "InputManager.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TestManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TrashTheCacheComponent.h"

// Standard includes
#include <cassert>

// SDL includes
#include <SDL.h>

#include "RotatorComponent.h"

void load()
{
    using namespace dae;

    const auto scene = SceneManager::GetInstance().CreateScene("Demo");

    // Background
    auto go = scene->AddGameObject();
    go->AddComponent<TextureComponent>("background.tga");

    // Text
    go = scene->AddGameObject();
    go->SetLocalPosition(80.0f, 20.0f);
    const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    const auto textComp = go->AddComponent<TextComponent>();
    textComp->SetFont(font);
    textComp->SetText("Programming 4 Assignment");

    // FPS
    go = scene->AddGameObject();
    go->SetLocalPosition(20.0f, 60.0f);
    const auto fpsComp = go->AddComponent<FPSComponent>();
    fpsComp->SetFont(font);
    fpsComp->SetText("FPS: ");

    // Trash the cache
    go = scene->AddGameObject();
    go->SetLocalPosition(50.0f, 100.0f);
    go->AddComponent<TrashTheCacheComponent>();

    // Root
    go = scene->AddGameObject("root");
    go->SetLocalPosition(320.0f, 240.0f);
    //---------------------------------------------------------------------------------
    // PACMAN
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject("pacman");
    go->SetLocalPosition(50.0f, 0.0f);
    go->AddComponent<RotatorComponent>();
    go->AddComponent<TextureComponent>("pacman.tga");
    go->SetParent(scene->FindGameObject("root"), false);

    // Arrow keys
    auto moveLeftCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand1 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand1    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_LEFT, std::move(moveLeftCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_RIGHT, std::move(moveRightCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_UP, std::move(moveUpCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_DOWN, std::move(moveDownCommand1));


    //---------------------------------------------------------------------------------
    // GHOST
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject("ghost1");
    go->SetLocalPosition(0.0f, 50.0f);
    go->AddComponent<TextureComponent>("ghost.tga");
    go->AddComponent<RotatorComponent>();
    go->SetParent(scene->FindGameObject("pacman"), false);
    
    // WASD
    auto moveLeftCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand2 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand2    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_a, std::move(moveLeftCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_d, std::move(moveRightCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_w, std::move(moveUpCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_s, std::move(moveDownCommand2));

    // Controller
    auto moveLeftCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand3 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand3    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_LEFT, std::move(moveLeftCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_RIGHT, std::move(moveRightCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_UP, std::move(moveUpCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_DOWN, std::move(moveDownCommand3));
    
    go = scene->AddGameObject("ghost2");
    go->SetLocalPosition(-50.0f, -50.0f);
    go->AddComponent<TextureComponent>("ghost.tga");
    go->SetParent(scene->FindGameObject("ghost1"), false);
}

int main(int, char*[])
{
    using namespace dae;
    
    Minigin engine("../Data/");
    TestManager::GetInstance().RunAllTests();
    engine.Run(load);
    return 0;
}
