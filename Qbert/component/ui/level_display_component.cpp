#include "level_display_component.h"

// Project includes
#include "component/player/level_counter_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void level_display_component::awake()
    {
        sprite_ui_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
    }

    void level_display_component::on_enable()
    {
        sprite_ui_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
    }

    void level_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "update_level_display")
        {
            auto const level_comp_ptr = static_cast<level_counter_component*>(subject_ptr);
            auto const level = level_comp_ptr->level();
            sprite_ui_comp_ptr_->sprite()->set_current_frame(level);
        }
    }
}
