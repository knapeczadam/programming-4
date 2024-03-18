#include "GameObject.h"

// Project includes
#include "BaseComponent.h"

// Standard includes
#include <ranges>

namespace dae
{
    void GameObject::Update()
    {
        for (const auto& pComponent : m_componentMap | std::views::values)
        {
            pComponent->Update();
        }
    }

    void GameObject::AddComponent(std::unique_ptr<BaseComponent> componentPtr)
    {
        m_componentMap[componentPtr->GetType()] = std::move(componentPtr);
    }

    bool GameObject::RemoveComponent(const ComponentType type)
    {
        if (m_componentMap.contains(type))
        {
            m_componentMap.erase(type);
            return true;
        }
        return false;
    }

    bool GameObject::HasComponent(ComponentType type) const
    {
        return m_componentMap.contains(type);
    }

    std::optional<BaseComponent*> GameObject::GetComponent(const ComponentFamily type) const
    {
        for (const auto& value : m_componentMap | std::views::values)
        {
            if (value->GetFamily() == type)
            {
                return value.get();
            }
        }
        return std::nullopt;
    }

    std::optional<BaseComponent*> GameObject::GetComponent(const ComponentType type) const
    {
        if (m_componentMap.contains(type))
        {
            return m_componentMap.at(type).get();
        }
        return std::nullopt;
    }

    std::unordered_map<ComponentType, BaseComponent*> GameObject::GetComponents() const
    {
        std::unordered_map<ComponentType, BaseComponent*> components{};
        for (const auto& [key, value] : m_componentMap)
        {
            components[key] = value.get();
        }
        return components;
    }

    void GameObject::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }

    void GameObject::SetPosition(const float x, const float y, const float z)
    {
        m_transform.SetPosition(x, y, z); 
    }
}
