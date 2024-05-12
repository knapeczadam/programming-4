#include "round_display_component.h"

// Project includes
#include "component/level/round_counter_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void round_display_component::awake()
    {
        sprite_ui_component_ptr_ = get_owner()->get_component<mngn::sprite_ui_component>();
    }

    void round_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "round_changed")
        {
            auto const *round_component_ptr = dynamic_cast<qbert::round_counter_component*>(subject_ptr);
            auto round = round_component_ptr->get_round();
            sprite_ui_component_ptr_->get_sprite()->set_current_frame(round);
        }
    }
}
