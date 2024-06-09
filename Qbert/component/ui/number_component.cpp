#include "number_component.h"

// Project includes
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <deque>

namespace qbert
{
    number_component::number_component(int number, int sprite_id, int texture_id)
        : number_{number}
        , sprite_id_{sprite_id}
        , texture_id_{texture_id}
    {
    }

    void number_component::awake()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
    }

    void number_component::on_enable()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
        set_number(number_);
    }

    void number_component::start()
    {
        set_number(number_);
    }

    void number_component::set_number(int number)
    {
        std::deque<mngn::sprite*> sprites;
        if (number == 0)
        {
            auto const sprite_ptr = mngn::sprite_manager::instance().load_sprite(sprite_id_,  texture_id_, false);
            sprites.push_front(sprite_ptr);
        }
        for (; number > 0; number /= 10)
        {
            auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(sprite_id_,  texture_id_, false);
            sprite_ptr->set_current_frame(number % 10);
            sprites.push_front(sprite_ptr);
        }
        multisprite_ui_comp_ptr_->set_sprites({ sprites.begin(), sprites.end()});
    }
}
