#pragma once

// Project includes
#include "BaseComponent.h"
#include "GameObject.h"

// Standard includes
#include <memory>
#include <string>

#include "RenderComponent.h"


namespace dae
{
    // Forward declarations
    class Font;
    class Texture2D;

    class TextComponent : public RenderComponent
    {
    public:
        TextComponent(std::string text, std::shared_ptr<Font> font);
        ~TextComponent() override = default;
        
        TextComponent(const TextComponent& other)            = delete;
        TextComponent(TextComponent&& other)                 = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other)      = delete;
        
        void Update() override;
        void Render() const override;

        ComponentType GetType() const override { return ComponentType::Text; }

        void SetText(const std::string& text);

    private:
        bool m_needsUpdate;
        std::string m_text;
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
    };
}
