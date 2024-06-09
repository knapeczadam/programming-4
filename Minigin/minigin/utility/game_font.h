#pragma once

// Standard includes
#include <string>

// Forward declarations
struct _TTF_Font;

namespace mngn
{
    /**
     * Simple RAII wrapper for a _TTF_Font
     */
    class game_font final
    {
    public:
        explicit game_font(std::string const &full_path, unsigned int size);
        ~game_font();

        game_font(game_font const &other)             = delete;
        game_font(game_font &&other)                  = delete;
        game_font &operator=(game_font const &other)  = delete;
        game_font &operator=(game_font &&other)       = delete;

        [[nodiscard]] auto font() const -> _TTF_Font *;

    private:
        _TTF_Font *font_ptr_ = nullptr;
    };
}
