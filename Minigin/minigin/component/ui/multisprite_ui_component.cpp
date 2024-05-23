#include "multisprite_ui_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace mngn
{
    multisprite_ui_component::multisprite_ui_component() = default;
    
    multisprite_ui_component::multisprite_ui_component(std::vector<sprite *> const &sprites, multisprite_orientation orientation, unsigned int spacing)
        : sprites_{sprites}
        , orientation_{orientation}
        , spacing_{spacing}
    {
    }

    multisprite_ui_component::multisprite_ui_component(multisprite_orientation orientation, unsigned int spacing)
        : orientation_{orientation}
        , spacing_{spacing}
    {
    }

    multisprite_ui_component::~multisprite_ui_component() = default;

    void multisprite_ui_component::render_ui() const
    {
        SDL_Rect dst_rect{};
        for (int i = 0; i < std::ssize(sprites_); ++i)
        {
            sprite *sprite = sprites_[i];
            auto src = sprite->src_rect();
            auto dst = sprite->dst_rect();
            auto const &pos = owner()->world_position();
            
            SDL_Rect src_rect;
            src_rect.x = src.left;
            src_rect.y = src.bottom;
            src_rect.w = src.width;
            src_rect.h = src.height;

            if (i == 0)
            {
                dst_rect.x = static_cast<int>(pos.x);
                dst_rect.y = static_cast<int>(pos.y);
            }
            else
            {
                if (orientation_ == multisprite_orientation::horizontal)
                {
                    dst_rect.x += dst.width + spacing_;
                }
                else
                {
                    dst_rect.y += dst.height + spacing_;
                }
            }
            
            dst_rect.w = dst.width;
            dst_rect.h = dst.height;
            
            renderer::instance().render_texture(*sprite->texture(), src_rect, dst_rect);
        }
    }

    void multisprite_ui_component::update()
    {
        if (animated_)
        {
            for (auto const &sprite_ptr : sprites_)
            {
                if (sprite_ptr->animated()) sprite_ptr->update(game_time::instance().delta_time());
            }
        }
    }
}
