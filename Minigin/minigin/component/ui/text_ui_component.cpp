#include "text_ui_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/renderer.h"
#include "minigin/core/resource_manager.h"
#include "minigin/utility/game_font.h"
#include "minigin/utility/texture.h"

// Standard includes
#include <stdexcept>
#include <utility>

// SDL includes
#include <SDL_ttf.h>

namespace mngn
{
    text_ui_component::text_ui_component() = default;
    
    text_ui_component::~text_ui_component() = default;

    void text_ui_component::update()
    {
        if (needs_update_)
        {
            constexpr SDL_Color color = {255, 255, 255, 255}; // only white text is supported now
            auto const surface_ptr = TTF_RenderText_Blended_Wrapped(font_ptr_->font(), text_.c_str(), color, 9999);
            if (surface_ptr == nullptr)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
        
            auto texture_ptr = SDL_CreateTextureFromSurface(renderer::instance().sdl_renderer(), surface_ptr);
            if (texture_ptr == nullptr)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
        
            SDL_FreeSurface(surface_ptr);
            text_texture_.reset();
            text_texture_ = std::make_unique<texture>(texture_ptr);
            needs_update_ = false;
        }
    }

    void text_ui_component::render_ui() const
    {
        if (text_texture_)
        {
            auto const &pos = owner()->world_position();
            renderer::instance().render_texture(*text_texture_, pos.x, pos.y);
        }
    }

    // This implementation uses the "dirty flag" pattern
    void text_ui_component::set_text(std::string const &text)
    {
        text_ = text;
        needs_update_ = true;
    }

    void text_ui_component::set_font(game_font *font_ptr)
    {
        font_ptr_ = font_ptr;
        needs_update_ = true;
    }

    void text_ui_component::set_font(std::string const &font, unsigned size)
    {
        font_ptr_ = resource_manager::instance().load_font(font, size);
        needs_update_ = true;
    }
}
