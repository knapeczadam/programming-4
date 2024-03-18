#pragma once

// Project includes
#include "Transform.h"

// Standard includes
#include <memory>
#include <optional>
#include <unordered_map>

namespace dae
{
    // Forward declarations
    class BaseComponent;
    enum class ComponentType;
    enum class ComponentFamily;
    
    class GameObject final
    {
    public:
        GameObject()  = default;
        ~GameObject() = default;
        
        GameObject(const GameObject& other)            = delete;
        GameObject(GameObject&& other)                 = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other)      = delete;

        void Update();

        void AddComponent(std::unique_ptr<BaseComponent> componentPtr);
        bool RemoveComponent(ComponentType type);
        bool HasComponent(ComponentType type) const;
        
        std::optional<BaseComponent*> GetComponent(ComponentFamily type) const;
        std::optional<BaseComponent*> GetComponent(ComponentType type) const;
        std::unordered_map<ComponentType, BaseComponent*> GetComponents() const;

        const glm::vec3& GetPosition() const { return m_transform.GetPosition(); }

        void SetPosition(const glm::vec2& position);
        void SetPosition(const glm::vec3& position);
        void SetPosition(float x, float y);
        void SetPosition(float x, float y, float z);

    private:
        Transform m_transform{};
        
        std::unordered_map<ComponentType, std::unique_ptr<BaseComponent>> m_componentMap{};
    };
}
