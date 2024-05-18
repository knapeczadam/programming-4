#include "game_over_state.h"

#include "core/factory.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    game_over_state::game_over_state()
    {
        scene_ptr_ = mngn::scene_manager::instance().create_scene("duo");
        scene_ptr_->set_active(false);
    	
		factory::ui::text_config_info text_config{};
		text_config.scene_ptr      = scene_ptr_;
		text_config.name           = "text_game_over";
		text_config.local_position = {176.0f, 288.0f};
		text_config.sprite_id      = qb_sp_alphabet_regular_purple;
		text_config.texture_id     = qb_re_t_sprite_general;
		text_config.space_sprite_id = qb_sp_alphabet_regular_space;
		text_config.space_texture_id = qb_re_t_sprite_general;
		text_config.text           = "game over";
		factory::ui::create_flickering_text(text_config);
    }

    void game_over_state::on_enter()
    {
	    scene_ptr_->set_active(true);
    }

    void game_over_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
