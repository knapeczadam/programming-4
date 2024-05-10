#include "cube_component.h"

#include <utility>

// Project includes
#include "minigin/component/sprite_component.h"
#include "minigin/core/game_component.h"
#include "minigin/core/game_object.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    cube_component::cube_component(std::vector<mngn::sprite*> colors, bool revertible)
        : colors_{std::move(colors)}
        , revertible_{revertible}
    {
    }

    void cube_component::awake()
    {
        get_owner()->get_component<mngn::sprite_component>()->set_sprite(colors_[0]);
    }

    void cube_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "debug")
        {
            subject_ptr = nullptr;
            // auto go = dynamic_cast<game_component*>(subject_ptr);
            // auto pos = go->get_owner()->get_local_position();
            // auto diff_x = get_owner()->get_local_position().x - pos.x;
            // auto diff_y = get_owner()->get_local_position().y - pos.y;
            // if (diff_x <= 16.0f and diff_y <= 12.0f)
            // {
                if (revertible_)
                {
                    current_color_ = (current_color_ + 1) % colors_.size();
                }
                else if (current_color_ < colors_.size() - 1)
                {
                    ++current_color_;
                }
            get_owner()->get_component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
            // }
        }
    }
}
