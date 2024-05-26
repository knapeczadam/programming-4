#include "menu_state.h"

// Project includes
#include "component/ui/number_component.h"
#include "core/factory.h"
#include "core/progress_manager.h"
#include "core/scene_utility.h"
#include "minigin/core/game_object.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    menu_state::menu_state(game_state_component *game_state_comp_ptr)
        : game_state{game_state_comp_ptr}
    {
    }

    void menu_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("menu");
        scene_ptr_->set_active(true);
        scene_ptr_->set_tag("current");
        scene_ptr_ = mngn::scene_manager::instance().find("menu_1");
        scene_ptr_->set_active(true);

        mngn::renderer::instance().set_background_color({49, 32, 115, 0});

        disk_ptr_ = scene_ptr_->find("disk");
        disk_ptr_->set_local_position(start_pos_);
    }

    void menu_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= switch_time_)
        {
            accu_time_ = 0.0f;
            if (menu_switched_)
            {
                switch_menu("menu_2", "menu_1");
            }
            else
            {
                switch_menu("menu_1", "menu_2");
            }
        }
        if (not menu_switched_)
        {
            animate_qbert();   
        }
    }

    void menu_state::on_exit()
    {
        progress_manager::instance().reset();
        
        progress_manager::instance().use_coin();
        auto number_comp_ptr = scene_utility::instance().current_scene()->find_game_objects_with_tag("coin").front()->component<number_component>();
        number_comp_ptr->set_number(progress_manager::instance().coins());
        
        auto scene_ptr = scene_utility::instance().current_scene();
        scene_ptr->clear_tag();
        scene_ptr->set_active(false);
        
        scene_ptr_->set_active(false);
    }

    void menu_state::switch_menu(const std::string &from_menu, const std::string &to_menu)
    {
        scene_ptr_ = mngn::scene_manager::instance().find(from_menu);
        scene_ptr_->set_active(false);
        scene_ptr_ = mngn::scene_manager::instance().find(to_menu);
        scene_ptr_->set_active(true);
        menu_switched_ = not menu_switched_;
    }

    void menu_state::animate_qbert()
    {
        glm::vec2 curr_pos = disk_ptr_->local_position();
        if (curr_pos != end_pos_)
        {
            curr_pos = glm::mix(start_pos_, end_pos_, glm::clamp(accu_time_ / switch_time_, 0.0f, 1.0f));
            disk_ptr_->set_local_position(curr_pos);
        }
        else
        {
            disk_ptr_->set_local_position(start_pos_);
        }
    }
}
