#include "waiting_state.h"

// Project includes
#include "flying_state.h"
#include "start_state.h"
#include "component/state/character_state_component.h"
#include "component/character/position_component.h"
#include "component/character/direction_component.h"
#include "component/level/disk_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    waiting_state::waiting_state(mngn::game_object* character_ptr, float waiting_time)
        : character_state{character_ptr}
        , waiting_time_{waiting_time}
    {
    }

    void waiting_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= waiting_time_)
        {
            character_ptr_->component<character_state_component>()->change_state<start_state>(character_ptr_);
            accu_time_ = 0.0f;
        }
    }

    void waiting_state::on_exit()
    {
        character_ptr_->set_local_position(224.0f, 84.0f);
        character_ptr_->component<position_component>()->reset();
        character_ptr_->component<direction_component>()->reset();
        character_ptr_->component<position_component>()->update_position();

        auto scene_ptr = mngn::scene_manager::instance().find_with_tag("current");
        auto flying_disk_go_ptrs = scene_ptr->find_game_objects_with_tag("flying_disk");
        if (not flying_disk_go_ptrs.empty())
        {
            auto flying_disk_go_ptr = flying_disk_go_ptrs.front();
            flying_disk_go_ptr->component<disk_component>()->disable();
            flying_disk_go_ptr->clear_tags();
        }
    }
}
