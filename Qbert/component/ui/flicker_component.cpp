#include "flicker_component.h"

// Project includes
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    flicker_component::flicker_component(float delay)
        : delay_{delay}
        , accu_time_{-delay}
    {
    }

    void flicker_component::awake()
    {
        sprite_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
        sprite_ptr_           = sprite_comp_ptr_->get_sprite();
    }

    void flicker_component::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= flicker_time_)
        {
            sprite_comp_ptr_->set_sprite(sprite_comp_ptr_->get_sprite() ? nullptr : sprite_ptr_);
            accu_time_ = 0.0f;
        }
    }
}
