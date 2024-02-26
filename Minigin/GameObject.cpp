#include "GameObject.h"

// Project includes
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    GameObject::~GameObject() = default;

    void GameObject::Update()
    {
    }

    void GameObject::Render() const
    {
        const auto& pos = m_transform.GetPosition();
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }

    void GameObject::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }

    void GameObject::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}
