#include "GameObject.h"

// Project includes
#include "BaseComponent.h"

// Standard includes
#include <algorithm>
#include <ranges>

namespace dae
{
    GameObject::GameObject(std::string name)
        : m_name(std::move(name))
    {
    }

    GameObject::~GameObject() = default;

    void GameObject::Update()
    {
        for (const auto& pComponent : m_componentMap | std::views::values)
        {
            pComponent->Update();
        }
    }

    void GameObject::AddChild(GameObject* childPtr)
    {
        m_children.push_back(childPtr);
    }

    void GameObject::UpdateWorldPosition()
    {
        if (m_positionDirty)
        {
            if (m_parentPtr)
            {
                const auto newPos = m_parentPtr->GetWorldPosition() + m_transform.GetLocalPosition();
                m_transform.SetWorldPosition(newPos);
            }
            else
            {
                m_transform.SetWorldPosition(m_transform.GetLocalPosition());
            }
        }
        m_positionDirty = false;
    }

    void GameObject::LateUpdate()
    {
        if (m_positionDirty)
        {
            for (const auto& child : m_children)
            {
                child->m_positionDirty = true;
            }
        }
        UpdateWorldPosition();
    }

    bool GameObject::SetParent(GameObject* parentPtr, bool keepWorldPosition)
    {
        // SetParent has to do five things:
        // 1. Check if the new parent is valid (not itself or one of its children)
        // 2. Remove itself from the previous parent (if any).
        // 3. Set the given parent on itself.
        // 4. Add itself as a child to the given parent.
        // 5. Update position, rotation and scale

        if (parentPtr == this or m_parentPtr == parentPtr or HasChild(parentPtr))
        {
            return false;
        }
        if (parentPtr == nullptr)
        {
            SetLocalPosition(GetWorldPosition());
        }
        else
        {
            if (keepWorldPosition)
            {
                const auto newPos = GetWorldPosition() - parentPtr->GetWorldPosition();
                m_transform.SetLocalPosition(newPos);
            }
            m_positionDirty = true;
        }
        if (m_parentPtr)
        {
            m_parentPtr->RemoveChild(this);
        }
        m_parentPtr = parentPtr;
        if (m_parentPtr)
        {
            m_parentPtr->AddChild(this);
        }
        return true;
    }

    bool GameObject::HasChild(GameObject* childPtr) const
    {
        return std::ranges::any_of(m_children, [childPtr](const auto& child) { return child == childPtr || child->HasChild(childPtr); });
    }

    /// \brief The number of children the parent Transform has.
    /// \return 
    int GameObject::GetChildCount() const
    {
        return static_cast<int>(m_children.size());
    }

    /// \brief Returns the child GameObject at the specified index.
    /// \param index 
    /// \return 
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
    
    bool GameObject::RemoveComponent(const BaseComponent* componentPtr)
    {
        for (auto it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
        {
            if (it->second.get() == componentPtr)
            {
                m_componentMap.erase(it);
                return true;
            }
        }
        return false;
    }

    int GameObject::RemoveComponents(ComponentFamily familyType)
    {
    int count = 0;
    for (auto it = m_componentMap.begin(); it != m_componentMap.end();)
    {
        if (it->second->GetFamily() == familyType)
        {
            it = m_componentMap.erase(it);
            ++count;
        }
        else
        {
            ++it;
        }
    }
    return count;
    }

    bool GameObject::HasComponent(ComponentFamily familyType) const
    {
        return std::ranges::any_of(m_componentMap | std::views::values, [familyType](const auto& value) { return value->GetFamily() == familyType; });
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \param familyType 
    /// \return 
    ComponentMap GameObject::GetComponents(const ComponentFamily familyType) const
    {
        ComponentMap components{};
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
    /// \return 
    ComponentMap GameObject::GetComponents() const
    {
        ComponentMap components{};
        for (const auto& [key, value] : m_componentMap)
        {
            components[key] = value.get();
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \param familyType 
    /// \return 
    ComponentMultimap GameObject::GetComponentsInChildren(
        ComponentFamily familyType) const
    {
        ComponentMultimap components{};
        for (const auto& [key, value] : m_componentMap)
        {
            if (value->GetFamily() == familyType)
            {
                components.emplace(key, value.get());
            }
        }
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren(familyType))
            {
                components.emplace(key, value);
            }
        }
        return components;
    }


    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \return
    ComponentMultimap GameObject::GetComponentsInChildren() const
    {
        ComponentMultimap components{};
        for (const auto& [key, value] : m_componentMap)
        {
            components.emplace(key, value.get());
        }
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \param familyType 
    /// \return 
    ComponentMultimap GameObject::GetComponentsInParent(
        ComponentFamily familyType) const
    {
        ComponentMultimap components{};
        for (const auto& [key, value] : m_componentMap)
        {
            if (value->GetFamily() == familyType)
            {
                components.emplace(key, value.get());
            }
        }
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent(familyType))
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \return 
    ComponentMultimap GameObject::GetComponentsInParent() const
    {
        ComponentMultimap components{};
        for (const auto& [key, value] : m_componentMap)
        {
            components.emplace(key, value.get());
        }
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    const glm::vec3& GameObject::GetWorldPosition()
    {
        if (m_positionDirty)
        {
            UpdateWorldPosition();
        }
        return m_transform.GetWorldPosition();
    }

    const glm::vec3& GameObject::GetLocalPosition() const
    {
        return m_transform.GetLocalPosition();
    }

    void GameObject::SetLocalPosition(float x, float y)
    {
        SetLocalPosition(glm::vec3{x, y, m_transform.GetLocalPosition().z});
    }

    void GameObject::SetLocalPosition(float x, float y, float z)
    {
        SetLocalPosition(glm::vec3{x, y, z});
    }

    void GameObject::SetLocalPosition(const glm::vec2& position)
    {
        SetLocalPosition(glm::vec3{position, m_transform.GetLocalPosition().z});
    }

    void GameObject::SetLocalPosition(const glm::vec3& position)
    {
        m_transform.SetLocalPosition(position);
        m_positionDirty = true;
    }
}
