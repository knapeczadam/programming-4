#include "score_display_component.h"

// Project includes
#include "component/player/score_counter_component.h"
#include "component/ui/number_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void score_display_component::awake()
    {
        number_comp_ptr_ = owner()->component<number_component>();
    }

    void score_display_component::on_enable()
    {
        number_comp_ptr_ = owner()->component<number_component>();
    }

    void score_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "update_score_display")
        {
            auto const score_comp_ptr = dynamic_cast<score_counter_component*>(subject_ptr);
            auto score = score_comp_ptr->score();
            number_comp_ptr_->set_number(score);
        }
    }
}
