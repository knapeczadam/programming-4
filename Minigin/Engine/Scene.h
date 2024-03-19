#pragma once

// Project includes
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
    class Scene final
    {
        friend Scene& SceneManager::CreateScene(const std::string& name);

    public:
        ~Scene();
        
        Scene(const Scene& other)            = delete;
        Scene(Scene&& other)                 = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other)      = delete;

        void Add(std::shared_ptr<GameObject> object);
        void Remove(std::shared_ptr<GameObject> object);
        void RemoveAll();

        void Update();
        void Render() const;
        void RenderUI() const;

    private:
        explicit Scene(const std::string& name);

        std::string m_name;
        std::vector<std::shared_ptr<GameObject>> m_objects{};

        static unsigned int m_idCounter;
    };
}
