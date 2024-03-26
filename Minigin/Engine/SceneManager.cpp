#include "SceneManager.h"

// Project includes
#include "Scene.h"
#include "GameObject.h"

namespace dae
{
    void SceneManager::Update()
    {
        for (const auto& scene : m_scenes)
        {
            scene->Update();
        }
    }

    void SceneManager::LateUpdate()
    {
        for (const auto& scene : m_scenes)
        {
            scene->LateUpdate();
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

    SceneManager::SceneManager() = default;

    SceneManager::~SceneManager() = default;

    Scene* SceneManager::CreateScene(const std::string& name)
    {
        m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
        return m_scenes.back().get();
    }
}
