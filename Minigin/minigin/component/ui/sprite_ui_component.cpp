#include "sprite_ui_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace mngn
{
    sprite_ui_component::sprite_ui_component() = default;

    sprite_ui_component::sprite_ui_component(mngn::sprite *sprite_ptr)
        : sprite_ptr_{sprite_ptr}
    {
    }

    sprite_ui_component::sprite_ui_component(int sprite_id, int texture_id, bool cache)
    {
        sprite_ptr_ = sprite_manager::instance().load_sprite(sprite_id, texture_id, cache);
    }

    sprite_ui_component::~sprite_ui_component() = default;

    void sprite_ui_component::render_ui() const
    {
        if (sprite_ptr_)
        {
            auto src = sprite_ptr_->src_rect();
            auto dst = sprite_ptr_->dst_rect();
            auto const &pos = owner()->world_position();
            
            SDL_Rect src_rect;
            src_rect.x = src.left;
            src_rect.y = src.bottom;
            src_rect.w = src.width;
            src_rect.h = src.height;
            
            SDL_Rect dst_rect;
            dst_rect.x = static_cast<int>(pos.x);
            dst_rect.y = static_cast<int>(pos.y);
            dst_rect.w = dst.width;
            dst_rect.h = dst.height;


            renderer::instance().render_texture(*sprite_ptr_->texture(), src_rect, dst_rect);
        }
    }

    void sprite_ui_component::update()
    {
        if (sprite_ptr_ and animated_)
        {
            sprite_ptr_->update(game_time::instance().delta_time());
        }
    }
}
