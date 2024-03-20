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
#include "TestComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"

// Standard includes
#include <cassert>

// SDL includes
#include <SDL.h>

#include "TrashTheCacheComponent.h"

void test()
{
    using namespace dae;

    {
        GameObject go;
        go.AddComponent<TestComponent>();
        assert(go.GetComponents().size() == 1);
        assert(go.HasComponent(ComponentType::Test));
    }
    {
        GameObject go;
        assert(not go.SetParent(&go));
        assert(go.GetParent() == nullptr);
    }
    {
        GameObject go1;
        GameObject go2;
        assert(go1.SetParent(&go2));
        assert(go2.HasChild(&go1));
        assert(go2.GetChildCount() == 1);
        assert(go2.GetChildAt(0) == &go1);
        assert(go1.GetParent() == &go2);
    }
    {
        GameObject go1;
        GameObject go2;
        assert(go1.SetParent(&go2));
        assert(go1.SetParent(nullptr));
        assert(go1.GetParent() == nullptr);
    }
    {
        GameObject go1;
        GameObject go2;
        GameObject go3;
        assert(go3.SetParent(&go2));
        assert(go2.SetParent(&go1));
        assert(not go1.SetParent(&go3));
    }
}

void load()
{
    using namespace dae;
    
    auto scene = SceneManager::GetInstance().CreateScene("Demo");

    //---------------------------------------------------------------------------------
    // PACMAN
    //---------------------------------------------------------------------------------
    auto go = scene->AddGameObject();
    go->SetPosition(216.0f, 180.0f);

    const auto textureComp1 = go->AddComponent<TextureComponent>();
    textureComp1->SetTexture("pacman.tga");

    // Arrow keys
    auto moveLeftCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand1 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand1    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand1  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_LEFT, std::move(moveLeftCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_RIGHT, std::move(moveRightCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_UP, std::move(moveUpCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_DOWN, std::move(moveDownCommand1));

    // WASD
    auto moveLeftCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand2 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand2    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand2  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_a, std::move(moveLeftCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_d, std::move(moveRightCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_w, std::move(moveUpCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_s, std::move(moveDownCommand2));

    //---------------------------------------------------------------------------------
    // GHOST
    //---------------------------------------------------------------------------------
    go = scene->AddGameObject();
    go->SetPosition(100.0f, 100.0f);

    const auto textureComp2 = go->AddComponent<TextureComponent>();
    textureComp2->SetTexture("ghost.tga");

    // Controller
    auto moveLeftCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{-1, 0});
    auto moveRightCommand3 = std::make_unique<MoveCommand>(go, glm::vec2{1, 0});
    auto moveUpCommand3    = std::make_unique<MoveCommand>(go, glm::vec2{0, -1});
    auto moveDownCommand3  = std::make_unique<MoveCommand>(go, glm::vec2{0, 1});
    
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_LEFT, std::move(moveLeftCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_RIGHT, std::move(moveRightCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_UP, std::move(moveUpCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_DOWN, std::move(moveDownCommand3));

    /*
    go = scene->AddGameObject();
    const auto textureComp3 = go->AddComponent<TextureComponent>();
    textureComp3->SetTexture("background.tga");
    
    go = scene->AddGameObject();
    go->SetPosition(80.0f, 20.0f);
    const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    const auto textComp = go->AddComponent<TextComponent>();
    textComp->SetFont(font);
    textComp->SetText("Programming 4 Assignment");
    
    go = scene->AddGameObject();
    go->SetPosition(20.0f, 60.0f);
    const auto fpsComp = go->AddComponent<FPSComponent>();
    fpsComp->SetFont(font);
    fpsComp->SetText("FPS: ");
    
    go = scene->AddGameObject();
    go->SetPosition(50.0f, 100.0f);
    go->AddComponent<TrashTheCacheComponent>();
    */
}

int main(int, char*[])
{
    using namespace dae;
    
    Minigin engine("../Data/");
    test();
    engine.Run(load);
    return 0;
}
