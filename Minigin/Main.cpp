// Visual Leak Detector
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// Project includes
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Time.h"

// SDL includes
#include <SDL.h>

#include "FPSComponent.h"

void load()
{
    using namespace dae;
    
    auto& scene = SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<GameObject>();
    auto textureComp = std::make_shared<TextureComponent>("background.tga");
    go->AddComponent(textureComp);
    scene.Add(go);

    go = std::make_shared<GameObject>();
    // go->SetTexture("logo.tga");
    // go->SetPosition(216, 180);
    textureComp = std::make_shared<TextureComponent>("logo.tga");
    textureComp->SetPosition(216, 180);
    go->AddComponent(textureComp);
    scene.Add(go);

    go = std::make_shared<GameObject>();
    auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textComp = std::make_shared<TextComponent>("Programming 4 Assignment", font);
    textComp->SetPosition(80, 20);
    go->AddComponent(textComp);
    scene.Add(go);

    go = std::make_shared<GameObject>();
    textComp = std::make_shared<FPSComponent>(font);
    textComp->SetPosition(20, 60);
    go->AddComponent(textComp);
    scene.Add(go);
}

int main(int, char*[])
{
    using namespace dae;
    
    Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}
