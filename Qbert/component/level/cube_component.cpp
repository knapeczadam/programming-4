#include "cube_component.h"

#include <utility>

// Project includes
#include "component/player/position_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    cube_component::cube_component(int row_id, int col_id, std::vector<mngn::sprite*> colors, bool revertible)
        : row_id_{row_id}
        , col_id_{col_id}
        , revertible_{revertible}
        , colors_{std::move(colors)}
    {
    }

    void cube_component::awake()
    {
        get_owner()->get_component<mngn::sprite_component>()->set_sprite(colors_[0]);
    }

    void cube_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "position_changed")
        {
            auto position_comp_ptr = dynamic_cast<position_component*>(subject_ptr);
            if (position_comp_ptr->get_row() == row_id_ and position_comp_ptr->get_col() == col_id_)
            {
                if (revertible_)
                {
                    current_color_ = (current_color_ + 1) % colors_.size();
                }
                else if (current_color_ < colors_.size() - 1)
                {
                    ++current_color_;
                }
                get_owner()->get_component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
            }
        }
    }
}
