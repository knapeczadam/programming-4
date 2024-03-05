#pragma once

// Standard includes
#include <string>

// Forward declarations
struct _TTF_Font;

namespace dae
{
    /**
     * Simple RAII wrapper for a _TTF_Font
     */
    class Font final
    {
    public:
        explicit Font(const std::string& fullPath, unsigned int size);
        ~Font();

        Font(const Font&)             = delete;
        Font(Font&&)                  = delete;
        Font& operator=(const Font&)  = delete;
        Font& operator=(const Font&&) = delete;
        
        _TTF_Font* GetFont() const;

    private:
        _TTF_Font* m_font;
    };
}
