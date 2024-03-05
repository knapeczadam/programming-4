#include "Font.h"

// SDL includes
#include <SDL_ttf.h>

// Standard includes
#include <stdexcept>

namespace dae
{
    TTF_Font* Font::GetFont() const
    {
        return m_font;
    }

    Font::Font(const std::string& fullPath, unsigned int size) : m_font(nullptr)
    {
        m_font = TTF_OpenFont(fullPath.c_str(), size);
        if (m_font == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
        }
    }

    Font::~Font()
    {
        TTF_CloseFont(m_font);
    }
}