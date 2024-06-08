#include "initial_manager.h"

// Project includes
#include "component/state/game_state_component.h"
#include "core/audio_player.h"
#include "core/factory.h"
#include "core/progress_manager.h"
#include "core/resources.h"
#include "core/scene_utility.h"
#include "core/score_manager.h"
#include "core/sprites.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/utility/sprite.h"
#include "state/game/scoreboard_state.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    void initial_manager::move_input(int dir)
    {
        curr_input_ = (curr_input_ + dir) % max_input_;
        if (curr_input_ < 0)
        {
            curr_input_ = max_input_ - 1;
        }
        
        move_underline();
    }

    void initial_manager::accept_input()
    {
        switch (curr_input_)
        {
        case space:
            if (initial_.length() < 3) initial_ += ' ';
            break;
        case dot:
            if (initial_.length() < 3) initial_ += '.';
            break;
        case backspace:
            if (not initial_.empty())
            {
                initial_.pop_back();
            }
            break;
        case end:
            {
               save_initial();
                audio_player::instance().play(audio::initial_end);
                auto game_state_comp_ptr = scene_utility::instance().game_state();
                game_state_comp_ptr->change_state<scoreboard_state>(game_state_comp_ptr);
            }
            break;
        default:
            if (initial_.length() < 3) initial_ += static_cast<char>(curr_input_ + 'A');
            break;
        }
        
        if (initial_.length() == 3)
        {
            curr_input_ = end;
            move_underline();
        }
        
        render_initials();
    }

    void initial_manager::save_initial()
    {
        auto score = progress_manager::instance().score();
        auto initial = initial_.empty() ? "   " : initial_;
        score_manager::instance().set_score(score, initial);
        score_manager::instance().save_scoreboard();
        reset();
    }

    void initial_manager::move_underline()
    {
        auto scene_ptr    = mngn::scene_manager::instance().find("input");
        auto unerline_ptr = scene_ptr->find_game_objects_with_tag("active").front();
        auto input_ptr    = scene_ptr->find_game_objects_with_tag(std::to_string(curr_input_)).front();
        
        auto new_pos = input_ptr->local_position();
        float constexpr offset = 16.0f;
        new_pos.y += offset;
        
        if (curr_input_ == backspace or curr_input_ == end)
        {
            new_pos.y += offset;
        }
        
        unerline_ptr->set_local_position(new_pos);
    }

    void initial_manager::render_initials()
    {
        auto scene_ptr     = mngn::scene_manager::instance().find("input");
        auto initial_ptr   = scene_ptr->find("final_initial");
        auto underline_ptr = scene_ptr->find("final_initial_underline");
        if (initial_ptr) scene_ptr->remove(initial_ptr);
        if (underline_ptr) scene_ptr->remove(underline_ptr);
        
        factory::ui::text_config_info text_config{};
        text_config.scene_ptr        = scene_ptr;
        text_config.name             = "final_initial";
        text_config.local_position   = {272.0f, 464.0f};
        text_config.text             = initial_;
        text_config.sprite_id        = qb_sp_alphabet_regular_purple;
        text_config.texture_id       = qb_re_t_sprite_general;
        text_config.space_sprite_id  = qb_sp_alphabet_regular_space;
        text_config.space_texture_id = qb_re_t_sprite_general;
        text_config.dot_sprite_id    = qb_sp_alphabet_regular_special;
        text_config.dot_texture_id   = qb_re_t_sprite_general;
        text_config.dot_frame        = 16;
        factory::ui::create_text(text_config);
        
    	std::vector<mngn::sprite*> sprites;
    	std::generate_n(std::back_inserter(sprites), initial_.length(), []
		{
			auto sprite_ptr =  mngn::sprite_manager::instance().load_sprite(qb_sp_alphabet_regular_special, qb_re_t_sprite_general, false);
			sprite_ptr->set_current_frame(11);
    		return sprite_ptr;	
		});

    	factory::ui::multisprite_config_info multisprite_config{};
    	multisprite_config.scene_ptr      = scene_ptr;
    	multisprite_config.name           = "final_initial_underline";
    	multisprite_config.local_position = {272.0f, 480.0f};
    	multisprite_config.sprites		  = sprites;
        factory::ui::create_multisprite(multisprite_config);
    }

    void initial_manager::reset()
    {
        initial_ = "";
        curr_input_ = 0;
        move_underline();
    }
}
