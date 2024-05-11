#include "sprite_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace mngn
{
    sprite_component::sprite_component() = default;

    sprite_component::sprite_component(sprite *sprite_ptr)
        : sprite_ptr_{sprite_ptr}
    {
    }

    sprite_component::sprite_component(int sprite_id, int texture_id, bool cache)
    {
        sprite_ptr_ = sprite_manager::get_instance().load_sprite(sprite_id, texture_id, cache);
    }

    sprite_component::~sprite_component() = default;

    void sprite_component::render() const
    {
        if (sprite_ptr_)
        {
            auto src = sprite_ptr_->get_src_rect();
            auto dst = sprite_ptr_->get_dst_rect();
            auto const &pos = get_owner()->get_world_position();
            
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


            renderer::get_instance().render_texture(*sprite_ptr_->get_texture(), src_rect, dst_rect);
        }
    }

    void sprite_component::update()
    {
        if (sprite_ptr_)
        {
            sprite_ptr_->update(game_time::get_instance().delta_time);
        }
    }
}
