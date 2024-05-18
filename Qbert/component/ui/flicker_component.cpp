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
        if (owner()->has_component<mngn::sprite_ui_component>())
        {
            sprite_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
        }
        else if (owner()->has_component<mngn::multisprite_ui_component>())
        {
            sprite_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
        }
    }

    void flicker_component::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time;
        if (accu_time_ >= flicker_time_)
        {
            sprite_comp_ptr_->set_enabled(not sprite_comp_ptr_->enabled());
            accu_time_ = 0.0f;
        }
    }
}
