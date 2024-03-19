#include "GameObject.h"

// Project includes
#include "BaseComponent.h"

// Standard includes
#include <algorithm>
#include <ranges>

namespace dae
{
    GameObject::GameObject(const glm::vec2& position)
    {
        m_transform.SetPosition(position);
    }

    GameObject::GameObject(float x, float y)
    {
        m_transform.SetPosition(x, y);
    }

    void GameObject::Update()
    {
        for (const auto& pComponent : m_componentMap | std::views::values)
        {
            pComponent->Update();
        }
    }

    bool GameObject::SetParent(GameObject* parentPtr)
    {
        // SetParent has to do five things:
        // 1. Check if the new parent is valid (not itself or one of its children)
        // 2. Remove itself from the previous parent (if any).
        // 3. Set the given parent on itself.
        // 4. Add itself as a child to the given parent.
        // 5. Update position, rotation and scale
        
        if (parentPtr == this)
        {
            return false;
        }
        if (HasChild(parentPtr))
        {
            return false;
        }
        if (m_parentPtr)
        {
            m_parentPtr->RemoveChild(this);
            m_parentPtr = nullptr;
        }
        m_parentPtr = parentPtr;
        if (m_parentPtr)
        {
            m_parentPtr->m_children.push_back(this);
        }
        return true;
    }

    bool GameObject::HasChild(GameObject* childPtr) const
    {
        return std::ranges::any_of(m_children, [childPtr](const auto& child) { return child == childPtr || child->HasChild(childPtr); });
    }

    int GameObject::GetChildCount() const
    {
        return static_cast<int>(m_children.size());
    }

    GameObject* GameObject::GetChildAt(int index) const
    {
        if (index < 0 || index >= static_cast<int>(m_children.size()))
        {
            return nullptr;
        }
        return m_children.at(index);
    }

    void GameObject::RemoveChild(GameObject* childPtr)
    {
        m_children.erase(std::ranges::remove(m_children, childPtr).begin(), m_children.end());
    }

    std::optional<std::unique_ptr<BaseComponent>> GameObject::RemoveComponent(const ComponentType componentType)
    {
        if (m_componentMap.contains(componentType))
        {
            std::unique_ptr<BaseComponent> componentPtr = std::move(m_componentMap.at(componentType));
            m_componentMap.erase(componentType);
            return componentPtr;
        }
        return std::nullopt;
    }

    bool GameObject::HasComponent(ComponentFamily familyType) const
    {
        return std::ranges::any_of(m_componentMap | std::views::values, [familyType](const auto& value) { return value->GetFamily() == familyType; });
    }

    bool GameObject::HasComponent(ComponentType componentType) const
    {
        return m_componentMap.contains(componentType);
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified.
    /// \param componentType 
    /// \return 
    BaseComponent* GameObject::GetComponent(ComponentType componentType) const
    {
        if (m_componentMap.contains(componentType))
        {
            return m_componentMap.at(componentType).get();
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \param familyType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponents(const ComponentFamily familyType) const
    {
        std::unordered_map<ComponentType, BaseComponent*> components{};
        for (const auto& [key, value] : m_componentMap)
        {
            if (value->GetFamily() == familyType)
            {
                components[key] = value.get();
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \param componentType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponents(ComponentType componentType) const
    {
        std::unordered_map<ComponentType, BaseComponent*> components{};
        if (m_componentMap.contains(componentType))
        {
            components[componentType] = m_componentMap.at(componentType).get();
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponents() const
    {
        std::unordered_map<ComponentType, BaseComponent*> components{};
        for (const auto& [key, value] : m_componentMap)
        {
            components[key] = value.get();
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any child of the GameObject.
    /// \param componentType 
    /// \return 
    BaseComponent* GameObject::GetComponentInChildren(ComponentType componentType) const
    {
        if (HasComponent(componentType))
        {
            return GetComponent(componentType);
        }
        for (const auto& child : m_children)
        {
            if (const auto componentPtr = child->GetComponentInChildren(componentType))
            {
                return componentPtr;
            }
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \param familyType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInChildren(ComponentFamily familyType) const
    {
        std::unordered_map<ComponentType, BaseComponent*> components = GetComponents(familyType);
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren(familyType))
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \param componentType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInChildren(ComponentType componentType) const
    {
        std::unordered_map<ComponentType, BaseComponent*> components = GetComponents(componentType);
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren(componentType))
            {
                components[key] = value;
            }
        }
        return components;
        
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \return
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInChildren() const
    {
        std::unordered_map<ComponentType, BaseComponent*> components = GetComponents();
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren())
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any parent of the GameObject.
    /// \param componentType 
    /// \return 
    BaseComponent* GameObject::GetComponentInParent(ComponentType componentType) const
    {
        if (HasComponent(componentType))
        {
            return GetComponent(componentType);
        }
        if (m_parentPtr)
        {
            return m_parentPtr->GetComponentInParent(componentType);
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \param familyType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInParent(ComponentFamily familyType) const
    {
        auto components = GetComponents(familyType);
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent(familyType))
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \param componentType 
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInParent(ComponentType componentType) const
    {
        std::unordered_map<ComponentType, BaseComponent*> components = GetComponents(componentType);
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent(componentType))
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \return 
    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponentsInParent() const
    {
        std::unordered_map<ComponentType, BaseComponent*> components = GetComponents();
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent())
            {
                components[key] = value;
            }
        }
        return components;
    }

    void GameObject::SetPosition(const glm::vec2& position)
    {
        m_transform.SetPosition(position);
    }

    void GameObject::SetPosition(const glm::vec3& position)
    {
        m_transform.SetPosition(position);
    }

    void GameObject::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y);
    }

    void GameObject::SetPosition(const float x, const float y, const float z)
    {
        m_transform.SetPosition(x, y, z); 
    }
}
