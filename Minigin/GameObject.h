#pragma once

// Project includes
#include "Transform.h"

// Standard includes
#include <memory>
#include <vector>

namespace dae
{
    // Forward declarations
    class BaseComponent;
    class Texture2D;

    class GameObject final
    {
    public:
        GameObject() = default;
        ~GameObject();
        
        GameObject(const GameObject& other)            = delete;
        GameObject(GameObject&& other)                 = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other)      = delete;

        void Update();
        void Render() const;

        void AddComponent(std::shared_ptr<BaseComponent> component);
        virtual void SetPosition(float x, float y) final;

    private:
        Transform m_transform{};
        
        std::vector<std::shared_ptr<BaseComponent>> m_components{};
    };
}
