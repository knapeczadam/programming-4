#include "menu_state.h"

// Project includes
#include "core/factory.h"
#include "core/resources.h"
#include "core/sprites.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"

namespace qbert
{
    menu_state::menu_state()
    {
        scene_ptr_ = mngn::scene_manager::instance().create_scene("menu");
        scene_ptr_->set_active(false);
        
        factory::ui::sprite_config_info sprite_config{};
        sprite_config.scene_ptr      = scene_ptr_;
        sprite_config.name           = "text_qbert";
        sprite_config.local_position = {38, 36};
        sprite_config.sprite_id      = qb_sp_text_qbert;
        factory::ui::create_sprite(sprite_config);

        factory::ui::text_config_info text_config{};
        text_config.scene_ptr       = scene_ptr_;
        text_config.name            = "credits";
        text_config.local_position  = {338, 66};
        text_config.text            = "credits";
        text_config.sprite_id       = qb_sp_alphabet_regular_green;
        text_config.texture_id      = qb_re_t_sprite_general;
        text_config.space_sprite_id = qb_sp_alphabet_regular_space;
        factory::ui::create_text(text_config);

        text_config.name = "row_1";
        text_config.local_position = {98, 114};
        text_config.text = "jump on squares to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_2";
        text_config.local_position = {98, 130};
        text_config.text = "change them to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_3";
        text_config.local_position = {98, 146};
        text_config.text = "the target color";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_4";
        text_config.local_position = {114, 178};
        text_config.text = "stay on playfield";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_5";
        text_config.local_position = {114, 194};
        text_config.text = "jumping off results";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_6";
        text_config.local_position = {114, 210};
        text_config.text = "in a fatal plummet";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_7";
        text_config.local_position = {114, 226};
        text_config.text = "unless a disk is there";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_8";
        text_config.local_position = {130, 258};
        text_config.text = "avoid all objects";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_9";
        text_config.local_position = {130, 274};
        text_config.text = "and creatures that";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_10";
        text_config.local_position = {130, 290};
        text_config.text = "are not green";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_11";
        text_config.local_position = {146, 322};
        text_config.text = "use spinning disks";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_12";
        text_config.local_position = {146, 338};
        text_config.text = "to lure snake to";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_14";
        text_config.local_position = {146, 354};
        text_config.text = "his death";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_15";
        text_config.local_position = {162, 386};
        text_config.text = "extra life at";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_16";
        text_config.local_position = {258, 402};
        text_config.text = "and each";
        factory::ui::create_text(text_config);
        
        text_config.name = "row_17";
        text_config.local_position = {162, 418};
        text_config.text = "additional";
        factory::ui::create_text(text_config);

        factory::ui::number_config_info number_config{};
        number_config.scene_ptr      = scene_ptr_;
        number_config.name           = "number_1";
        number_config.local_position = {176, 402};
        number_config.number         = 8000;
        number_config.sprite_id      = qb_sp_numbers_regular_orange;
        number_config.texture_id     = qb_re_t_sprite_general;
        factory::ui::create_number(number_config);
        
        number_config.name           = "number_2";
        number_config.local_position = {336, 418};
        number_config.number         = 14000;
        factory::ui::create_number(number_config);
    }

    void menu_state::on_enter()
    {
        scene_ptr_->set_active(true);
    }

    void menu_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }
}
