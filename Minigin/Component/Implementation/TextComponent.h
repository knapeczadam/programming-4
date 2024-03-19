#pragma once

// Project includes
#include "RenderComponent.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class Font;
    class Texture2D;

    class TextComponent : public RenderComponent
    {
    public:
        TextComponent() = default;
        TextComponent(std::string text, std::shared_ptr<Font> font);
        virtual ~TextComponent() override = default;
        
        TextComponent(const TextComponent& other)            = delete;
        TextComponent(TextComponent&& other)                 = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other)      = delete;
        
        void Update() override;
        void Render() const override;

        virtual ComponentType GetType() const override { return ComponentType::Text; }

        void SetText(const std::string& text);
        void SetFont(std::shared_ptr<Font> font);

    private:
        bool m_needsUpdate = true;
        std::string m_text;
        std::shared_ptr<Font> m_font = nullptr;
        std::shared_ptr<Texture2D> m_textTexture = nullptr;
    };
}
