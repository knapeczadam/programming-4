#include "SceneManager.h"

// Project includes
#include "Scene.h"

namespace dae
{
    void SceneManager::Update()
    {
        for (auto& scene : m_scenes)
        {
            scene->Update();
        }
    }
    
    void SceneManager::Render()
    {
        for (const auto& scene : m_scenes)
        {
            scene->Render();
        }
    }

    void SceneManager::RenderUI()
    {
        for (const auto& scene : m_scenes)
        {
            scene->RenderUI();
        }
    }

    Scene* SceneManager::CreateScene(const std::string& name)
    {
        m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
        return m_scenes.back().get();
    }
}
