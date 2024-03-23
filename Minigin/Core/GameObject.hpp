#pragma once

namespace dae
{
    // Forward declaration
    class GameObject;

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified.
    /// \tparam T 
    /// \return 
    template <class T> requires IsComponentType<T>
    auto GameObject::GetComponent() const -> T*
    {
        if (HasComponent<T>())
        {
            return static_cast<T*>(m_componentMap.at(typeid(T)).get());
        }
        return nullptr;
    }

    template <class T> requires IsComponentFamilyType<T>
    auto GameObject::GetComponents() const -> T_ComponentMultimap<T>
    {
        T_ComponentMultimap<T> components;
        for (const auto& [key, value] : m_componentMap)
        {
            if (auto componentPtr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, componentPtr);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires IsComponentType<T>
    auto GameObject::GetComponentInChildren() const -> T*
    {
        if (auto componentPtr = GetComponent<T>())
        {
            return componentPtr;
        }
        for (const auto& child : m_children)
        {
            if (auto componentPtr = child->GetComponentInChildren<T>())
            {
                return componentPtr;
            }
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires IsComponentType<T>
    auto GameObject::GetComponentsInChildren() const -> T_ComponentMultimap<T>
    {
        T_ComponentMultimap<T> components;
        if (auto component = GetComponent<T>())
        {
            components.emplace(typeid(T), component);
        }
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    template <class T> requires IsComponentFamilyType<T>
    auto GameObject::GetComponentsInChildren() const -> T_ComponentMultimap<T>
    {
        T_ComponentMultimap<T> components;
        for (const auto& [key, value] : m_componentMap)
        {
            if (auto componentPtr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, componentPtr);
            }
        }
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires IsComponentType<T>
    auto GameObject::GetComponentInParent() const -> T*
    {
        if (auto componentPtr = GetComponent<T>())
        {
            return componentPtr;
        }
        if (m_parentPtr)
        {
            return m_parentPtr->GetComponentInParent<T>();
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires IsComponentType<T>
    auto GameObject::GetComponentsInParent() const -> T_ComponentMultimap<T> 
    {
        T_ComponentMultimap<T> components;
        if (auto component = GetComponent<T>())
        {
            components.emplace(typeid(T), component);
        }
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    template <class T> requires IsComponentFamilyType<T>
    auto GameObject::GetComponentsInParent() const -> T_ComponentMultimap<T>
    {
        T_ComponentMultimap<T> components;
        for (const auto& [key, value] : m_componentMap)
        {
            if (auto componentPtr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, componentPtr);
            }
        }
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Adds a component class of type componentType to the GameObject. 
    /// \tparam T 
    /// \return 
    template <class T, typename... Args> requires IsComponentType<T>
    auto GameObject::AddComponent(Args&&... args) -> T*
    {
        auto componentPtr = std::make_unique<T>(std::forward<Args>(args)...);
        componentPtr->SetOwner(this);
        auto copyPtr = componentPtr.get();
        m_componentMap[typeid(T)] = std::move(componentPtr);
        return copyPtr;
    }

    template <class T> requires IsComponentType<T>
    auto GameObject::RemoveComponent() -> bool
    {
        if (m_componentMap.contains(typeid(T)))
        {
            m_componentMap.erase(typeid(T));
            return true;
        }
        return false;
    }

    template <class T> requires IsComponentFamilyType<T>
    auto GameObject::RemoveComponents() -> int
    {
        int count = 0;
        for (auto it = m_componentMap.begin(); it != m_componentMap.end();)
        {
            if (dynamic_cast<T*>(it->second.get()))
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

    template <class T> requires IsComponentType<T>
    auto GameObject::HasComponent() const -> bool
    {
        return m_componentMap.contains(typeid(T));
    }

    template <class T> requires IsComponentFamilyType<T>
    auto GameObject::HasComponent() const -> bool
    {
        return std::ranges::any_of(m_componentMap, [](const auto& pair)
        {
            return dynamic_cast<T*>(pair.second.get());
        });
    }

    
}
