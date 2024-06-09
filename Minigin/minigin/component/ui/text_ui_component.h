#pragma once

// Project includes
#include "minigin/component/family/ui_component.h"

// Standard includes
#include <memory>
#include <string>

namespace mngn
{
    // Forward declarations
    class game_font;
    class texture;

    class text_ui_component : public ui_component
    {
    public:
        text_ui_component();
        ~text_ui_component() override;
        
        text_ui_component(text_ui_component const &other)            = delete;
        text_ui_component(text_ui_component &&other)                 = delete;
        text_ui_component &operator=(text_ui_component const &other) = delete;
        text_ui_component &operator=(text_ui_component &&other)      = delete;
        
        void update() override;
        void render_ui() const override;

        [[nodiscard]] auto get_text() const -> const std::string & { return text_; }
        void set_text(std::string const &text);
        void set_font(game_font *font_ptr);
        void set_font(std::string const &font, unsigned int size);

    private:
        std::string text_;
        bool                     needs_update_ = true;
        game_font                *font_ptr_    = nullptr;
        std::unique_ptr<texture> text_texture_ = nullptr;
    };
}
