﻿#include "sprites.h"

// Project includes
#include "minigin/core/sprite_manager.h"

namespace qbert
{
    void init_sprites()
    {
        using namespace mngn;
        sprite_manager::get_instance()
            .set_sprite_config_path("configs/sprite_config.json")
            .load_sprite_config();

        sprite_manager::get_instance()
            .add_sprite_pair(qb_sp_qbert_1, "qbert_1")
            .add_sprite_pair(qb_sp_qbert_2, "qbert_2")
            .add_sprite_pair(qb_sp_qbert_life, "qbert_life")
            .add_sprite_pair(qb_sp_qbert_curse, "qbert_curse")
            .add_sprite_pair(qb_sp_qbert_big, "qbert_big")
            .add_sprite_pair(qb_sp_ball_red, "ball_red")
            .add_sprite_pair(qb_sp_ball_green, "ball_green")
            .add_sprite_pair(qb_sp_coily_egg, "coily_egg")
            .add_sprite_pair(qb_sp_coily, "coily")
            .add_sprite_pair(qb_sp_ugg, "ugg")
            .add_sprite_pair(qb_sp_wrong_way, "wrong_way")
            .add_sprite_pair(qb_sp_slick, "slick")
            .add_sprite_pair(qb_sp_sam, "sam")
            .add_sprite_pair(qb_sp_numbers_regular_orange, "numbers_regular_orange")
            .add_sprite_pair(qb_sp_numbers_regular_purple, "numbers_regular_purple")
            .add_sprite_pair(qb_sp_numbers_bold_orange, "numbers_bold_orange")
            .add_sprite_pair(qb_sp_numbers_bold_pink, "numbers_bold_pink")
            .add_sprite_pair(qb_sp_alphabet_regular_green, "alphabet_regular_green")
            .add_sprite_pair(qb_sp_alphabet_regular_purple, "alphabet_regular_purple")
            .add_sprite_pair(qb_sp_alphabet_bold_orange, "alphabet_bold_orange")
            .add_sprite_pair(qb_sp_text_orange_player, "text_orange_player")
            .add_sprite_pair(qb_sp_text_purple_player, "text_purple_player")
            .add_sprite_pair(qb_sp_text_level, "text_level")
            .add_sprite_pair(qb_sp_text_round, "text_round")
            .add_sprite_pair(qb_sp_text_change_to, "text_change_to")
            .add_sprite_pair(qb_sp_text_qbert, "text_qbert")
            .add_sprite_pair(qb_sp_text_rotate_disk_color, "text_rotate_disk_color")
            .add_sprite_pair(qb_sp_text_one, "text_one")
            .add_sprite_pair(qb_sp_text_two, "text_two")
            .add_sprite_pair(qb_sp_arrow_left, "arrow_left")
            .add_sprite_pair(qb_sp_arrow_right, "arrow_right")
            .add_sprite_pair(qb_sp_level_1_disk_1, "level_1_disk_1")
            .add_sprite_pair(qb_sp_level_1_disk_2, "level_1_disk_2")
            .add_sprite_pair(qb_sp_level_2_disk_1, "level_2_disk_1")
            .add_sprite_pair(qb_sp_level_2_disk_2, "level_2_disk_2")
            .add_sprite_pair(qb_sp_level_3_disk_1, "level_3_disk_1")
            .add_sprite_pair(qb_sp_level_3_disk_2, "level_3_disk_2")
            .add_sprite_pair(qb_sp_level_1_red_cube_1, "level_1_red_cube_1")
            .add_sprite_pair(qb_sp_level_1_red_cube_2, "level_1_red_cube_2")
            .add_sprite_pair(qb_sp_level_1_red_cube_small, "level_1_red_cube_small")
            .add_sprite_pair(qb_sp_level_1_yellow_cube_1, "level_1_yellow_cube_1")
            .add_sprite_pair(qb_sp_level_1_yellow_cube_2, "level_1_yellow_cube_2")
            .add_sprite_pair(qb_sp_level_1_yellow_cube_small, "level_1_yellow_cube_small")
            .add_sprite_pair(qb_sp_level_1_blue_cube_1, "level_1_blue_cube_1")
            .add_sprite_pair(qb_sp_level_1_blue_cube_2, "level_1_blue_cube_2")
            .add_sprite_pair(qb_sp_level_1_blue_cube_small, "level_1_blue_cube_small")
            .add_sprite_pair(qb_sp_level_2_blue_cube_1, "level_2_blue_cube_1")
            .add_sprite_pair(qb_sp_level_2_blue_cube_2, "level_2_blue_cube_2")
            .add_sprite_pair(qb_sp_level_2_blue_cube_small, "level_2_blue_cube_small")
            .add_sprite_pair(qb_sp_level_2_yellow_cube_1, "level_2_yellow_cube_1")
            .add_sprite_pair(qb_sp_level_2_yellow_cube_2, "level_2_yellow_cube_2")
            .add_sprite_pair(qb_sp_level_2_yellow_cube_small, "level_2_yellow_cube_small")
            .add_sprite_pair(qb_sp_level_2_green_cube_1, "level_2_green_cube_1")
            .add_sprite_pair(qb_sp_level_2_green_cube_2, "level_2_green_cube_2")
            .add_sprite_pair(qb_sp_level_2_green_cube_small, "level_2_green_cube_small")
            .add_sprite_pair(qb_sp_level_3_white_cube_1, "level_3_white_cube_1")
            .add_sprite_pair(qb_sp_level_3_white_cube_2, "level_3_white_cube_2")
            .add_sprite_pair(qb_sp_level_3_white_cube_small, "level_3_white_cube_small")
            .add_sprite_pair(qb_sp_level_3_gray_cube_1, "level_3_gray_cube_1")
            .add_sprite_pair(qb_sp_level_3_gray_cube_2, "level_3_gray_cube_2")
            .add_sprite_pair(qb_sp_level_3_gray_cube_small, "level_3_gray_cube_small")
            .add_sprite_pair(qb_sp_level_3_blue_cube_1, "level_3_blue_cube_1")
            .add_sprite_pair(qb_sp_level_3_blue_cube_2, "level_3_blue_cube_2")
            .add_sprite_pair(qb_sp_level_3_blue_cube_small, "level_3_blue_cube_small")
            .add_sprite_pair(qb_sp_numbers_large_yellow, "numbers_large_yellow")
            .add_sprite_pair(qb_sp_numbers_large_gray, "numbers_large_gray")
            .add_sprite_pair(qb_sp_alphabet_large_yellow, "alphabet_large_yellow")
            .add_sprite_pair(qb_sp_alphabet_large_gray, "alphabet_large_gray")
            .add_sprite_pair(qb_sp_text_large_yellow_qbert, "text_large_yellow_qbert")
            .add_sprite_pair(qb_sp_text_large_gray_qbert, "text_large_gray_qbert");
    }
}
