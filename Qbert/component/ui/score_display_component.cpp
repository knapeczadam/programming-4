#include "score_display_component.h"

// Project includes
#include "component/player/score_component.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <deque>

namespace qbert
{
    void score_display_component::awake()
    {
        multisprite_ui_component_ptr_ = get_owner()->get_component<mngn::multisprite_ui_component>();
    }

    void score_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "score_changed")
        {
            auto const *score_component_ptr = dynamic_cast<score_component*>(subject_ptr);
            std::deque<mngn::sprite*> sprites;
            if (score_component_ptr)
            {
                auto score = score_component_ptr->get_score();
                if (score == 0)
                {
                    auto sprite_ptr = mngn::sprite_manager::get_instance().load_sprite(qb_sp_numbers_regular_orange,  qb_re_t_sprite_general, false);
                    sprites.push_front(sprite_ptr);
                }
                for (; score > 0; score /= 10)
                {
                    auto sprite_ptr = mngn::sprite_manager::get_instance().load_sprite(qb_sp_numbers_regular_orange,  qb_re_t_sprite_general, false);
                    sprite_ptr->set_current_frame(score % 10);
                    sprites.push_front(sprite_ptr);
                }
            }
            multisprite_ui_component_ptr_->set_sprites({ sprites.begin(), sprites.end()});
        }
    }
}
