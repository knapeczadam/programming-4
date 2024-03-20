#pragma once

// Project includes
#include "GameObject.h"

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

        GameObject* AddGameObject();
        void Remove(GameObject* object);
        void RemoveAll();

        void Update();
        void Render() const;
        void RenderUI() const;

    private:
        explicit Scene(const std::string& name);

        std::string m_name;
        std::vector<std::unique_ptr<GameObject>> m_objects{};

        static unsigned int m_idCounter;
    };
}
