#include "flying_state.h"

// Project includes
#include "component/level/disk_component.h"
#include "component/level/fly_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"

namespace qbert
{
    flying_state::flying_state(mngn::game_object *character_ptr, disk_component *disk_comp_ptr)
        : character_state{character_ptr}
        , disk_comp_ptr_{disk_comp_ptr}
    {
    }

    void flying_state::on_enter()
    {
        character_ptr_->set_parent(disk_comp_ptr_->owner());
        disk_comp_ptr_->owner()->component<fly_component>()->fly();
        disk_comp_ptr_->owner()->add_tag("flying_disk");
    }

    void flying_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ <= flash_time)
        {
            float t = glm::clamp(accu_time_ / flash_time, 0.0f, 1.0f);
            auto gradient_green = static_cast<Uint8>(glm::mix(185, 0, t));
            mngn::renderer::instance().set_background_color({0, gradient_green, 0, 1});
        }
    }

    void flying_state::on_exit()
    {
        accu_time_ = 0.0f;
    }
}
