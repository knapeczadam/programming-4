#include "level_display_component.h"

// Project includes
#include "component/level/level_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void level_display_component::awake()
    {
        sprite_ui_component_ptr_ = get_owner()->get_component<mngn::sprite_ui_component>();
    }

    void level_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "level_changed")
        {
            auto const *level_component_ptr = dynamic_cast<qbert::level_component*>(subject_ptr);
            auto level = level_component_ptr->get_level();
            sprite_ui_component_ptr_->get_sprite()->set_current_frame(level);
        }
    }
}
