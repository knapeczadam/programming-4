#include "alphabet_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/component/ui/multisprite_ui_component.h"
#include "minigin/utility/sprite.h"
#include "core/resources.h"
#include "core/sprites.h"

// Standard includes
#include <algorithm>
#include <cctype>
#include <ranges>
#include <vector>


namespace qbert
{
    alphabet_component::alphabet_component(std::string text, int sprite_id, int texture_id, int space_sprite_id, int space_texture_id)
        : text_{std::move(text)}
        , sprite_id_{sprite_id}
        , texture_id_{texture_id}
        , space_sprite_id_{space_sprite_id}
        , space_texture_id_{space_texture_id}
    {
    }

    void alphabet_component::awake()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
    }

    void alphabet_component::start()
    {
        set_text();
    }

    void alphabet_component::set_text()
    {
        std::vector<mngn::sprite*> sprites;
        for (auto const c : text_)
        {
            if (c == ' ')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(space_sprite_id_, space_texture_id_, false);
                sprites.push_back(sprite_ptr);
            }
            else
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(sprite_id_, texture_id_, false);
                sprite_ptr->set_current_frame(std::tolower(c) - 'a');
                sprites.push_back(sprite_ptr);
            }
        }
        multisprite_ui_comp_ptr_->set_sprites(sprites);
    }
}
