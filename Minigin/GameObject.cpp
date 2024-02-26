#include "GameObject.h"

// Project includes
#include "Renderer.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
}

void dae::GameObject::Render() const
{
    const auto& pos = m_transform.GetPosition();
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
    m_transform.SetPosition(x, y, 0.0f);
}
