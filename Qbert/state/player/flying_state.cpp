#include "flying_state.h"

// Project includes
#include "start_state.h"
#include "component/character/position_component.h"
#include "component/level/disk_component.h"
#include "component/level/fly_component.h"
#include "component/character/direction_component.h"
#include "component/state/character_state_component.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"

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
        if (frozen_) return;
        
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ <= flash_time)
        {
            float t = glm::clamp(accu_time_ / flash_time, 0.0f, 1.0f);
            auto gradient_green = static_cast<Uint8>(glm::mix(185, 0, t));
            mngn::renderer::instance().set_background_color({0, gradient_green, 0, 1});
        }
        if (accu_time_ >= fly_time_)
        {
            character_ptr_->component<character_state_component>()->change_state<start_state>(character_ptr_);
            accu_time_ = 0.0f;
        }
    }

    void flying_state::on_exit()
    {
        character_ptr_->set_local_position(224.0f, 84.0f);
        character_ptr_->component<position_component>()->reset();
        character_ptr_->component<direction_component>()->reset();
        character_ptr_->component<position_component>()->update_position();

        auto scene_ptr = scene_utility::instance().current_scene();
        auto flying_disk_go_ptrs = scene_ptr->find_game_objects_with_tag("flying_disk");
        if (not flying_disk_go_ptrs.empty())
        {
            auto flying_disk_go_ptr = flying_disk_go_ptrs.front();
            flying_disk_go_ptr->component<disk_component>()->disable();
            flying_disk_go_ptr->clear_tags();
        }
    }
}
