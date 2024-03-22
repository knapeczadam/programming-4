#pragma once

// Project includes
#include "Scene.h"
#include "Singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace dae
{
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene* CreateScene(const std::string& name);

        void Update();
        void LateUpdate();
        void Render();
        void RenderUI();

    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        
        std::vector<std::unique_ptr<Scene>> m_scenes;
    };
}
