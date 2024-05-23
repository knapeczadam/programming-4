#include "small_cube_component.h"

// Project includes
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"

namespace qbert
{
    small_cube_component::small_cube_component(int sprite_id, int texture_id)
    {
        animated_sprite_ptr_ = mngn::sprite_manager::instance().load_sprite(sprite_id, texture_id);
    }

    void small_cube_component::start()
    {
        sprite_ui_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
        original_sprite_ptr_ = sprite_ui_comp_ptr_->sprite();
    }

    void small_cube_component::on_enable()
    {
        sprite_ui_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
        original_sprite_ptr_ = sprite_ui_comp_ptr_->sprite();
    }

    void small_cube_component::on_disable()
    {
        sprite_ui_comp_ptr_->set_sprite(original_sprite_ptr_);
        sprite_ui_comp_ptr_->set_animated(false);
    }
    
    void small_cube_component::enable_animation()
    {
        sprite_ui_comp_ptr_->set_sprite(animated_sprite_ptr_);
        sprite_ui_comp_ptr_->set_animated(true);
    }
}
