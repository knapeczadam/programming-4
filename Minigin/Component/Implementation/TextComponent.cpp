#include "TextComponent.h"

// Project includes
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

// Standard includes
#include <stdexcept>
#include <utility>

// SDL includes
#include <SDL_ttf.h>

#include "ResourceManager.h"

namespace dae
{
    void TextComponent::Update()
    {
        if (m_needsUpdate)
        {
            constexpr SDL_Color color = {255, 255, 255, 255}; // only white text is supported now
            const auto surf = TTF_RenderText_Blended_Wrapped(m_font->GetFont(), m_text.c_str(), color, 9999);
            if (surf == nullptr)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
        
            auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            if (texture == nullptr)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
        
            SDL_FreeSurface(surf);
            m_textTexture.reset();
            m_textTexture = std::make_unique<Texture2D>(texture);
            m_needsUpdate = false;
        }
    }

    void TextComponent::RenderUI() const
    {
        if (m_textTexture)
        {
            const auto& pos = GetOwner()->GetWorldPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    // This implementation uses the "dirty flag" pattern
    void TextComponent::SetText(const std::string& text)
    {
        m_text = text;
        m_needsUpdate = true;
    }

    void TextComponent::SetFont(Font* font)
    {
        m_font = font;
        m_needsUpdate = true;
    }

    void TextComponent::SetFont(const std::string& font, unsigned size)
    {
        m_font = ResourceManager::GetInstance().LoadFont(font, size);
        m_needsUpdate = true;
    }
}
