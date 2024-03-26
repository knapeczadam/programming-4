#include "TextComponent.h"

// Project includes
#include "GameObject.h"
#include "Renderer.h"
#include "game_font.h"
#include "Texture2D.h"

// Standard includes
#include <stdexcept>
#include <utility>

// SDL includes
#include <SDL_ttf.h>

#include "ResourceManager.h"

namespace dae
{
    void text_component::update()
    {
        if (needs_update_)
        {
            constexpr SDL_Color color = {255, 255, 255, 255}; // only white text is supported now
            const auto surf = TTF_RenderText_Blended_Wrapped(font_->get_font(), text_.c_str(), color, 9999);
            if (surf == nullptr)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
        
            auto texture = SDL_CreateTextureFromSurface(renderer::get_instance().get_sdl_renderer(), surf);
            if (texture == nullptr)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
        
            SDL_FreeSurface(surf);
            text_texture_.reset();
            text_texture_ = std::make_unique<texture_2d>(texture);
            needs_update_ = false;
        }
    }

    void text_component::render_ui() const
    {
        if (text_texture_)
        {
            const auto& pos = get_owner()->get_world_position();
            renderer::get_instance().render_texture(*text_texture_, pos.x, pos.y);
        }
    }

    // This implementation uses the "dirty flag" pattern
    void text_component::set_text(const std::string& text)
    {
        text_ = text;
        needs_update_ = true;
    }

    void text_component::set_font(game_font* font)
    {
        font_ = font;
        needs_update_ = true;
    }

    void text_component::set_font(const std::string& font, unsigned size)
    {
        font_ = resource_manager::get_instance().load_font(font, size);
        needs_update_ = true;
    }
}
