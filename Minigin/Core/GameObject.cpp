#include "GameObject.h"

// Project includes
#include "BaseComponent.h"

namespace dae
{
    GameObject::~GameObject() = default;

    void GameObject::Update()
    {
        for (const auto& component : m_components)
        {
            component->Update();
        }
    }

    void GameObject::Render() const
    {
        for (const auto& component : m_components)
        {
            component->Render();
        }
    }

    void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
    {
        m_components.emplace_back(std::move(component));
    }
    
    void GameObject::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}
