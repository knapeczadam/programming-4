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
#include "MovementComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Timer.h"
#include "TrashTheCacheComponent.h"

// SDL includes
#include <SDL.h>


void load()
{
    using namespace dae;
    
    auto& scene = SceneManager::GetInstance().CreateScene("Demo");

    //---------------------------------------------------------------------------------
    // PACMAN
    //---------------------------------------------------------------------------------
    auto go = std::make_shared<GameObject>();
    go->SetPosition(216, 180);
    
    auto textureComp1 = std::make_unique<TextureComponent>("pacman.tga");
    textureComp1->SetOwner(go.get());
    go->AddComponent(std::move(textureComp1));
    
    auto movementComp1 = std::make_unique<MovementComponent>();
    movementComp1->SetOwner(go.get());
    go->AddComponent(std::move(movementComp1));
    
    scene.Add(go);

    // Arrow keys
    auto moveLeftCommand1  = std::make_unique<MoveLeftCommand>(go.get());
    auto moveRightCommand1 = std::make_unique<MoveRightCommand>(go.get());
    auto moveUpCommand1    = std::make_unique<MoveUpCommand>(go.get());
    auto moveDownCommand1  = std::make_unique<MoveDownCommand>(go.get());
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_LEFT, std::move(moveLeftCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_RIGHT, std::move(moveRightCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_UP, std::move(moveUpCommand1));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_DOWN, std::move(moveDownCommand1));

    // WASD
    auto moveLeftCommand2  = std::make_unique<MoveLeftCommand>(go.get());
    auto moveRightCommand2 = std::make_unique<MoveRightCommand>(go.get());
    auto moveUpCommand2    = std::make_unique<MoveUpCommand>(go.get());
    auto moveDownCommand2  = std::make_unique<MoveDownCommand>(go.get());
    
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_a, std::move(moveLeftCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_d, std::move(moveRightCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_w, std::move(moveUpCommand2));
    InputManager::GetInstance().BindCommand(InputType::Keyboard, InputState::Down, Input::K_s, std::move(moveDownCommand2));

    //---------------------------------------------------------------------------------
    // GHOST
    //---------------------------------------------------------------------------------
    go = std::make_shared<GameObject>();
    go->SetPosition(100, 100);
    
    auto textureComp2 = std::make_unique<TextureComponent>("ghost.tga");
    textureComp2->SetOwner(go.get());
    go->AddComponent(std::move(textureComp2));
    
    auto movementComp2 = std::make_unique<MovementComponent>();
    movementComp2->SetSpeed(2);
    movementComp2->SetOwner(go.get());
    go->AddComponent(std::move(movementComp2));
    
    scene.Add(go);

    // Controller
    auto moveLeftCommand3  = std::make_unique<MoveLeftCommand>(go.get());
    auto moveRightCommand3 = std::make_unique<MoveRightCommand>(go.get());
    auto moveUpCommand3    = std::make_unique<MoveUpCommand>(go.get());
    auto moveDownCommand3  = std::make_unique<MoveDownCommand>(go.get());
    
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_LEFT, std::move(moveLeftCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_RIGHT, std::move(moveRightCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_UP, std::move(moveUpCommand3));
    InputManager::GetInstance().BindCommand(InputType::Controller, InputState::Down, Input::C_DOWN, std::move(moveDownCommand3));

    /*
    go = std::make_shared<GameObject>();
    go->SetPosition(80, 20);
    auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textComp = std::make_unique<TextComponent>("Programming 4 Assignment", font);
    textComp->SetOwner(go.get());
    go->AddComponent(std::move(textComp));
    scene.Add(go);
    
    go = std::make_shared<GameObject>();
    go->SetPosition(20, 60);
    textComp = std::make_unique<FPSComponent>(font);
    textComp->SetOwner(go.get());
    go->AddComponent(std::move(textComp));
    scene.Add(go);
    
    go = std::make_shared<GameObject>();
    go->SetPosition(50, 100);
    auto uiComp = std::make_unique<TrashTheCacheComponent>();
    uiComp->SetOwner(go.get());
    go->AddComponent(std::move(uiComp));
    scene.Add(go);
    */
}

int main(int, char*[])
{
    using namespace dae;
    
    Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}
