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
    alphabet_component::alphabet_component(alphabet_config_info config_info)
        : config_info_{config_info}
    {
    }

    void alphabet_component::awake()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
    }

    void alphabet_component::on_enable()
    {
        multisprite_ui_comp_ptr_ = owner()->component<mngn::multisprite_ui_component>();
        set_text();
    }

    void alphabet_component::start()
    {
        set_text();
    }

    void alphabet_component::set_text()
    {
        std::vector<mngn::sprite*> sprites;
        for (auto const c : config_info_.text)
        {
            if (c == ' ')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.space_sprite_id, config_info_.space_texture_id, false);
                sprites.push_back(sprite_ptr);
            }
            else if (c == '.')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.dot_sprite_id, config_info_.dot_texture_id, false);
                sprite_ptr->set_current_frame(config_info_.dot_frame);
                sprites.push_back(sprite_ptr);
            }
            else if (c == '!')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.exclamation_sprite_id, config_info_.exclamation_texture_id, false);
                sprite_ptr->set_current_frame(config_info_.exclamation_frame);
                sprites.push_back(sprite_ptr);
            }
            else if (c == '@')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.at_sprite_id, config_info_.at_texture_id, false);
                sprite_ptr->set_current_frame(config_info_.at_frame);
                sprites.push_back(sprite_ptr);
            }
            else if (c == '=')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.equal_sprite_id, config_info_.equal_texture_id, false);
                sprite_ptr->set_current_frame(config_info_.equal_frame);
                sprites.push_back(sprite_ptr);
            }
            else if (c == '-')
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.hyphen_sprite_id, config_info_.hyphen_texture_id, false);
                sprite_ptr->set_current_frame(config_info_.hyphen_frame);
                sprites.push_back(sprite_ptr);
            }
            else
            {
                auto sprite_ptr = mngn::sprite_manager::instance().load_sprite(config_info_.sprite_id, config_info_.texture_id, false);
                sprite_ptr->set_current_frame(std::tolower(c) - 'a');
                sprites.push_back(sprite_ptr);
            }
        }
        multisprite_ui_comp_ptr_->set_sprites(sprites);
    }
}
