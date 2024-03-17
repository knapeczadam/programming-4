// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "FPSComponent.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Timer.h"

// SDL includes
#include <SDL.h>

#include "TrashTheCacheComponent.h"

void load()
{
    using namespace dae;
    
    auto& scene = SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<GameObject>();
    auto textureComp = std::make_unique<TextureComponent>("background.tga");
    textureComp->SetOwner(go.get());
    go->AddComponent(std::move(textureComp));
    scene.Add(go);
    
    go = std::make_shared<GameObject>();
    go->SetPosition(216, 180);
    textureComp = std::make_unique<TextureComponent>("logo.tga");
    textureComp->SetOwner(go.get());
    go->AddComponent(std::move(textureComp));
    scene.Add(go);
    
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
}

int main(int, char*[])
{
    using namespace dae;
    
    Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}
