#include "game_font.h"

// Standard includes
#include <stdexcept>

// SDL includes
#include <SDL_ttf.h>

namespace dae
{
    auto game_font::get_font() const -> TTF_Font *
    {
        return font_ptr_;
    }

    game_font::game_font(std::string const &full_path, unsigned int size) : font_ptr_(nullptr)
    {
        font_ptr_ = TTF_OpenFont(full_path.c_str(), static_cast<int>(size));
        if (font_ptr_ == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
        }
    }

    game_font::~game_font()
    {
        TTF_CloseFont(font_ptr_);
    }
}
