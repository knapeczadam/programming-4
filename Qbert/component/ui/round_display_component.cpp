#include "round_display_component.h"

// Project includes
#include "component/player/round_counter_component.h"
#include "minigin/component/ui/sprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void round_display_component::awake()
    {
        sprite_ui_comp_ptr_ = owner()->component<mngn::sprite_ui_component>();
    }

    void round_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "round_changed")
        {
            auto const round_counter_comp_ptr = dynamic_cast<round_counter_component*>(subject_ptr);
            auto round = round_counter_comp_ptr->round();
            sprite_ui_comp_ptr_->sprite()->set_current_frame(round);
        }
    }
}
