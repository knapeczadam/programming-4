#include "cube_component.h"

#include <utility>

// Project includes
#include "component/player/position_component.h"
#include "component/player/score_counter_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    cube_component::cube_component(int row_idx, int col_idx, std::vector<mngn::sprite*> colors, bool revertible)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
        , score_count_{static_cast<int>(colors.size()) - 1}
        , revertible_{revertible}
        , colors_{std::move(colors)}
    {
    }

    void cube_component::awake()
    {
        owner()->component<mngn::sprite_component>()->set_sprite(colors_[0]);
    }

    void cube_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "position_changed")
        {
            auto position_comp_ptr = dynamic_cast<position_component*>(subject_ptr);
            if (position_comp_ptr->row() == row_idx_ and position_comp_ptr->col() == col_idx_)
            {
                if (revertible_)
                {
                    current_color_ = (current_color_ + 1) % static_cast<int>(colors_.size());
                }
                else if (current_color_ < static_cast<int>(colors_.size()) - 1)
                {
                    ++current_color_;
                }
                if (score_count_ > 0)
                {
                    --score_count_;
                    position_comp_ptr->owner()->component<score_counter_component>()->add_score(25);
                }
                owner()->component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
            }
        }
    }
}
