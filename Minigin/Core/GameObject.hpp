﻿#pragma once
#include <ranges>

namespace dae
{
    // Forward declaration
    class GameObject;

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified.
    /// \tparam T 
    /// \return 
    template <typename T>
    T* GameObject::GetComponent() const
    {
        for (const auto& val : m_componentMap | std::views::values)
        {
            if (auto componentPtr = dynamic_cast<T*>(val.get()))
            {
                return componentPtr;
            }
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \tparam T 
    /// \return 
    template <typename T>
    std::unordered_map<ComponentType, T*> GameObject::GetComponents() const
    {
        std::unordered_map<ComponentType, T*> components{};
        for (const auto& [key, value] : m_componentMap)
        {
            if (auto componentPtr = dynamic_cast<T*>(value.get()))
            {
                components[key] = componentPtr;
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <typename T>
    T* GameObject::GetComponentInChildren() const
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
    template <typename T>
    std::unordered_map<ComponentType, T*> GameObject::GetComponentsInChildren() const
    {
        std::unordered_map<ComponentType, T*> components = GetComponents<T>();
        for (const auto& child : m_children)
        {
            for (const auto& [key, value] : child->GetComponentsInChildren<T>())
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <typename T>
    T* GameObject::GetComponentInParent() const
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
    template <typename T>
    std::unordered_map<ComponentType, T*> GameObject::GetComponentsInParent() const
    {
        std::unordered_map<ComponentType, T*> components = GetComponents<T>();
        if (m_parentPtr)
        {
            for (const auto& [key, value] : m_parentPtr->GetComponentsInParent<T>())
            {
                components[key] = value;
            }
        }
        return components;
    }

    /// \brief Adds a component class of type componentType to the GameObject. 
    /// \tparam T 
    /// \return 
    template <typename T>
    T* GameObject::AddComponent()
    {
        auto componentPtr = std::make_unique<T>();
        componentPtr->SetOwner(this);
        auto copyPtr = componentPtr.get();
        m_componentMap[componentPtr->GetType()] = std::move(componentPtr);
        return copyPtr;
    }
}
