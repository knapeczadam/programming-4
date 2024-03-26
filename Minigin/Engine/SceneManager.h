#pragma once

// Project includes
#include "Singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace dae
{
    // Forward declarations
    class Scene;

    // Type aliases
    using ScenePtr = std::unique_ptr<Scene>;
    
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        ~SceneManager() override;
        Scene* CreateScene(const std::string& name);

        void Update();
        void LateUpdate();
        void Render();
        void RenderUI();

    private:
        friend class Singleton<SceneManager>;
        SceneManager();
        
        std::vector<ScenePtr> m_scenes;
    };
}
