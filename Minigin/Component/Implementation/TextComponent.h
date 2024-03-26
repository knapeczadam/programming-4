#pragma once

// Project includes
#include "UIComponent.h"

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
        text_component() = default;
        ~text_component() override = default;
        
        text_component(const text_component& other)            = delete;
        text_component(text_component&& other)                 = delete;
        text_component& operator=(const text_component& other) = delete;
        text_component& operator=(text_component&& other)      = delete;
        
        void update() override;
        void render_ui() const override;

        [[nodiscard]] auto get_text() const -> const std::string& { return text_; }
        void set_text(const std::string& text);
        void set_font(game_font* font);
        void set_font(const std::string& font, unsigned int size);

    private:
        bool needs_update_ = true;
        std::string text_;
        game_font* font_ = nullptr;
        std::unique_ptr<texture_2d> text_texture_ = nullptr;
    };
}
