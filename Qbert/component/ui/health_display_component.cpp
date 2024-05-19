#include "health_display_component.h"

// Project includes
#include "component/player/health_component.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "minigin/core/game_object.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"

namespace qbert
{
    void health_display_component::start()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
    }

    void health_display_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "health_changed")
        {
            if (auto const health_comp = dynamic_cast<health_component*>(subject_ptr))
            {
                std::vector<mngn::sprite*> sprites;
                auto health = health_comp->health();
                for (auto i = 0; i < health; ++i)
                {
                    auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(qb_sp_qbert_life, qb_re_t_sprite_general);
                    sprites.push_back(sprite_ptr);
                }
                multisprite_ui_comp_ptr_->set_sprites(sprites);
            }
        }
    }
}
