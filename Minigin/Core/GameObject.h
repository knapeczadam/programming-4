#pragma once

// Project includes
#include "BaseComponent.h"
#include "Transform.h"

// Standard includes
#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace dae
{
    // Forward declarations
    enum class ComponentType;
    enum class ComponentFamily;

    // Concepts
    template <class T>
    concept IsComponentType = std::is_base_of_v<BaseComponent, T> and std::is_constructible_v<T>;

    template <class T>
    concept IsComponentFamilyType = std::is_base_of_v<BaseComponent, T> and std::is_abstract_v<T>;

    // Type aliases
    using ComponentMap = std::unordered_map<std::type_index, BaseComponent*>;
    using ComponentMultimap = std::unordered_multimap<std::type_index, BaseComponent*>;
    
    template <class T>
    using T_ComponentMultimap = std::unordered_multimap<std::type_index, T*>;

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

        auto GetName() const -> std::string { return m_name; }

        void Update();
        void UpdateWorldPosition();
        void LateUpdate();

        auto IsAlive() const -> bool { return m_alive; }
        void Destroy() { m_alive = false; }

        auto GetParent() const -> GameObject* { return m_parentPtr; }
        auto SetParent(GameObject* parentPtr, bool keepWorldPosition = true) -> bool;
        auto HasChild(GameObject* childPtr) const -> bool;

        auto GetChildCount() const -> int;
        auto GetChildAt(int index) const -> GameObject*;

        auto RemoveComponent(const BaseComponent* componentPtr) -> bool;
        
        auto HasComponent(ComponentFamily familyType) const -> bool;

        auto GetComponents(ComponentFamily familyType) const -> ComponentMap;
        auto GetComponents() const -> ComponentMap;

        auto GetComponentsInChildren(ComponentFamily familyType) const -> ComponentMultimap;
        auto GetComponentsInChildren() const -> ComponentMultimap;

        auto GetComponentsInParent(ComponentFamily familyType) const -> ComponentMultimap;
        auto GetComponentsInParent() const -> ComponentMultimap;

        template <class T, typename... Args> requires IsComponentType<T>
        auto AddComponent(Args&&... args) -> T*;

        template <class T> requires IsComponentType<T>
        auto GetComponent() const -> T*;

        template <class T> requires IsComponentFamilyType<T>
        auto GetComponents() const -> T_ComponentMultimap<T>;

        template <class T> requires IsComponentType<T>
        auto GetComponentInChildren() const -> T*;

        template <class T> requires IsComponentType<T>
        auto GetComponentsInChildren() const -> T_ComponentMultimap<T>;

        template <class T> requires IsComponentFamilyType<T>
        auto GetComponentsInChildren() const -> T_ComponentMultimap<T>;

        template <class T> requires IsComponentType<T>
        auto GetComponentInParent() const -> T*;

        template <class T> requires IsComponentType<T>
        auto GetComponentsInParent() const -> T_ComponentMultimap<T>;

        template <class T> requires IsComponentFamilyType<T>
        auto GetComponentsInParent() const -> T_ComponentMultimap<T>;

        template <class T> requires IsComponentType<T>
        auto RemoveComponent() -> bool;

        template <class T> requires IsComponentFamilyType<T>
        auto RemoveComponents() -> int;

        template <class T> requires IsComponentType<T>
        auto HasComponent() const -> bool;

        template <class T> requires IsComponentFamilyType<T>
        auto HasComponent() const -> bool;

        const glm::vec3& GetWorldPosition();
        const glm::vec3& GetLocalPosition() const;

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
        bool m_alive          = true;

        // TODO: switch to map?
        std::unordered_map<std::type_index, std::unique_ptr<BaseComponent>> m_componentMap = {};

        GameObject* m_parentPtr = nullptr;
        std::vector<GameObject*> m_children = {};
    };
}

#include "GameObject.hpp"
