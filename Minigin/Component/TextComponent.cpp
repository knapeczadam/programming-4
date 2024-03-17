#include "TextComponent.h"

// Project includes
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

// SDL includes
#include <SDL_ttf.h>

// Standard includes
#include <stdexcept>

namespace dae
{
    TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font)
        : m_needsUpdate(true), m_text(std::move(text)), m_font(std::move(font)), m_textTexture(nullptr)
    {
    }

    void TextComponent::Update()
    {
        if (m_needsUpdate)
        {
            constexpr SDL_Color color = {255, 255, 255, 255}; // only white text is supported now
            const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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
            m_textTexture = std::make_shared<Texture2D>(texture);
            m_needsUpdate = false;
        }
    }

    void TextComponent::Render() const
    {
        if (m_textTexture != nullptr)
        {
            const auto& pos = GetOwner()->GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    // This implementation uses the "dirty flag" pattern
    void TextComponent::SetText(const std::string& text)
    {
        m_text = text;
        m_needsUpdate = true;
    }
}
