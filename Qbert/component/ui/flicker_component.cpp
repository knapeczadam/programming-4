#include "flicker_component.h"

// Project includes
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/component/ui/multisprite_ui_component.h"
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
        if (auto sprite_ui_comp_ptr = owner()->component<mngn::sprite_ui_component>())
        {
            sprite_comp_ptr_ = sprite_ui_comp_ptr;
        }
        else if (auto multisprite_ui_comp_ptr = owner()->component<mngn::multisprite_ui_component>())
        {
            sprite_comp_ptr_ = multisprite_ui_comp_ptr;
        }
    }

    void flicker_component::on_enable()
    {
        is_flickering_ = true;

        if (auto sprite_ui_comp_ptr = owner()->component<mngn::sprite_ui_component>())
        {
            sprite_comp_ptr_ = sprite_ui_comp_ptr;
        }
        else if (auto multisprite_ui_comp_ptr = owner()->component<mngn::multisprite_ui_component>())
        {
            sprite_comp_ptr_ = multisprite_ui_comp_ptr;
        }
    }

    void flicker_component::update()
    {
        if (is_flickering_)
        {
            accu_time_ += mngn::game_time::instance().delta_time();
            if (accu_time_ >= flicker_time_)
            {
                sprite_comp_ptr_->set_enabled(not sprite_comp_ptr_->enabled());
                accu_time_ = 0.0f;
            }
        }
    }

    void flicker_component::on_disable()
    {
        is_flickering_ = false;
        accu_time_     = -delay_;
    }
}
