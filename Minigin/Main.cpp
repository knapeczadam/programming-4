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
#include "TextObject.h"

// SDL includes
#include <SDL.h>

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<dae::GameObject>();
    go->SetTexture("background.tga");
    scene.Add(go);

    go = std::make_shared<dae::GameObject>();
    go->SetTexture("logo.tga");
    go->SetPosition(216, 180);
    scene.Add(go);

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    const auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
    to->SetPosition(80, 20);
    scene.Add(to);
}

int main(int, char*[])
{
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}
