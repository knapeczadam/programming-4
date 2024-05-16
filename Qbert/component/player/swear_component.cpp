#include "swear_component.h"

// Project includes
#include "health_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"

namespace qbert
{
    void swear_component::awake()
    {
        swearing_go_ptr_ = owner()->find("swearing");
        swearing_go_ptr_->set_active(false);
    }

    void swear_component::update()
    {
        if (is_swearing_)
        {
            accu_time_ += mngn::game_time::instance().delta_time;
            if (accu_time_ >= swear_time_)
            {
                swearing_go_ptr_->set_active(false);
                is_swearing_ = false;
                accu_time_  = 0.0f;

                owner()->component<health_component>()->take_damage(1);
            }
        }
    }

    void swear_component::swear()
    {
        swearing_go_ptr_->set_active(true);
        is_swearing_ = true;
    }
}
