#pragma once

// Project includes
#include "UIComponent.h"

// Standard includes
#include <memory>
#include <string>


namespace dae
{
    // Forward declarations
    class Font;
    class Texture2D;

    class TextComponent : public UIComponent
    {
    public:
        TextComponent() = default;
        virtual ~TextComponent() override = default;
        
        TextComponent(const TextComponent& other)            = delete;
        TextComponent(TextComponent&& other)                 = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other)      = delete;
        
        virtual void Update() override;
        virtual void RenderUI() const override;

        void SetText(const std::string& text);
        void SetFont(Font* font);
        void SetFont(const std::string& font, unsigned int size);

    private:
        bool m_needsUpdate = true;
        std::string m_text;
        Font* m_font = nullptr;
        std::unique_ptr<Texture2D> m_textTexture = nullptr;
    };
}
