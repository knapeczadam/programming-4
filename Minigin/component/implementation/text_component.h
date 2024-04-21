#pragma once

// Project includes
#include "component/family/ui_component.h"

// Standard includes
#include <memory>
#include <string>


namespace dae
{
    // Forward declarations
    class game_font;
    class texture_2d;

    class text_component : public ui_component
    {
    public:
        text_component()           = default;
        ~text_component() override = default;
        
        text_component(text_component const &other)            = delete;
        text_component(text_component &&other)                 = delete;
        text_component &operator=(text_component const &other) = delete;
        text_component &operator=(text_component &&other)      = delete;
        
        void update() override;
        void render_ui() const override;

        [[nodiscard]] auto get_text() const -> const std::string & { return text_; }
        void set_text(std::string const &text);
        void set_font(game_font *font_ptr);
        void set_font(std::string const &font, unsigned int size);

    private:
        std::string text_;
        bool                        needs_update_ = true;
        game_font                   *font_ptr_    = nullptr;
        std::unique_ptr<texture_2d> text_texture_ = nullptr;
    };
}
