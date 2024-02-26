#pragma once

// Project includes
#include "GameObject.h"
#include "Transform.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class Font;
    class Texture2D;

    class TextObject final
    {
    public:
        TextObject(const std::string& text, std::shared_ptr<Font> font);
        ~TextObject() = default;
        
        TextObject(const TextObject& other)            = delete;
        TextObject(TextObject&& other)                 = delete;
        TextObject& operator=(const TextObject& other) = delete;
        TextObject& operator=(TextObject&& other)      = delete;
        
        void Update();
        void Render() const;

        void SetText(const std::string& text);
        void SetPosition(float x, float y);

    private:
        bool m_needsUpdate;
        std::string m_text;
        Transform m_transform{};
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
    };
}
