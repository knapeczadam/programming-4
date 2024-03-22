#pragma once

// Project includes
#include "BaseComponent.h"
#include "Transform.h"

// Standard includes
#include <memory>
#include <string>
#include <unordered_map>

namespace dae
{
    // Forward declarations
    enum class ComponentType;
    enum class ComponentFamily;

    class GameObject final
    {
    public:
        GameObject() = default;
        explicit GameObject(std::string name);
        ~GameObject() = default;

        GameObject(const GameObject& other)            = delete;
        GameObject(GameObject&& other)                 = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other)      = delete;

        std::string GetName() const { return m_name; }

        void Update();
        void UpdateWorldPosition();
        void LateUpdate();

        GameObject* GetParent() const { return m_parentPtr; }
        bool SetParent(GameObject* parentPtr, bool keepWorldPosition = true);
        bool HasChild(GameObject* childPtr) const;

        int GetChildCount() const;
        GameObject* GetChildAt(int index) const;

        bool RemoveComponent(ComponentType componentType);
        bool RemoveComponent(const BaseComponent* componentPtr);
        int RemoveComponents(ComponentFamily familyType);
        
        bool HasComponent(ComponentFamily familyType) const;
        bool HasComponent(ComponentType componentType) const;

        BaseComponent* GetComponent(ComponentType componentType) const;
        std::unordered_map<ComponentType, BaseComponent*> GetComponents(ComponentFamily familyType) const;
        std::unordered_map<ComponentType, BaseComponent*> GetComponents() const;

        BaseComponent* GetComponentInChildren(ComponentType componentType) const;
        std::unordered_multimap<ComponentType, BaseComponent*> GetComponentsInChildren(ComponentFamily familyType) const;
        std::unordered_multimap<ComponentType, BaseComponent*> GetComponentsInChildren(ComponentType componentType) const;
        std::unordered_multimap<ComponentType, BaseComponent*> GetComponentsInChildren() const;

        BaseComponent* GetComponentInParent(ComponentType componentType) const;
        std::unordered_map<ComponentType, BaseComponent*> GetComponentsInParent(ComponentFamily familyType) const;
        std::unordered_multimap<ComponentType, BaseComponent*> GetComponentsInParent(ComponentType componentType) const;
        std::unordered_multimap<ComponentType, BaseComponent*> GetComponentsInParent() const;

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args);

        template <typename T>
        T* GetComponent() const;

        template <typename T>
        T* GetComponentInChildren() const;

        template <typename T>
        std::unordered_multimap<ComponentType, T*> GetComponentsInChildren() const;

        template <typename T>
        T* GetComponentInParent() const;

        template <typename T>
        std::unordered_multimap<ComponentType, T*> GetComponentsInParent() const;

        const glm::vec3& GetWorldPosition();
        [[nodiscard]] const glm::vec3& GetLocalPosition() const;

        void SetLocalPosition(float x, float y);
        void SetLocalPosition(float x, float y, float z);
        void SetLocalPosition(const glm::vec2& position);
        void SetLocalPosition(const glm::vec3& position);

    private:
        void AddChild(GameObject* childPtr);
        void RemoveChild(GameObject* childPtr);

    private:
        std::string m_name    = {};
        Transform m_transform = {};
        bool m_positionDirty  = false;

        // TODO: switch to map?
        std::unordered_map<ComponentType, std::unique_ptr<BaseComponent>> m_componentMap = {};

        GameObject* m_parentPtr = nullptr;
        std::vector<GameObject*> m_children = {};
    };
}

#include "GameObject.hpp"
