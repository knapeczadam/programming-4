﻿#include "TextureComponent.h"

// Project includes
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    TextureComponent::TextureComponent(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }

    void TextureComponent::Render() const
    {
        const auto& pos = GetOwner()->GetPosition();
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }
}
