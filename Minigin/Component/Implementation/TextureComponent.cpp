#include "TextureComponent.h"

// Project includes
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    TextureComponent::TextureComponent(const std::string& filename)
        : m_texture(ResourceManager::GetInstance().LoadTexture(filename))
    {
    }

    void TextureComponent::Render() const
    {
        if (m_texture)
        {
            const auto& pos = GetOwner()->GetWorldPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }
}
