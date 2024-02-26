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

    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene& CreateScene(const std::string& name);

        void Update();
        void FixedUpdate();
        void Render();

    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        std::vector<std::shared_ptr<Scene>> m_scenes;
    };
}
