#pragma once

// Project includes
#include "GameObject.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class SceneManager;
    
    class Scene final
    {
        friend class SceneManager;

    public:
        ~Scene() = default;
        
        Scene(const Scene& other)            = delete;
        Scene(Scene&& other)                 = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other)      = delete;

        GameObject* AddGameObject(const std::string& name = "New Game Object");
        void RemoveGameObject(GameObject* object);
        void RemoveAll();
        int GetGameObjectCount() const;
        GameObject* FindGameObject(const std::string& name) const;

        void Update();
        void LateUpdate();
        void Render() const;
        void RenderUI() const;

    private:
        explicit Scene(std::string name);

        std::string m_name;
        std::vector<std::unique_ptr<GameObject>> m_objects{};

        static unsigned int m_idCounter;
    };
}
