#include "jumping_state.h"

// Project includes
#include "component/player/face_component.h"
#include "component/player/jump_component.h"
#include "component/player/position_idx_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    jumping_state::jumping_state(mngn::game_object *player_ptr, int row_dir, int col_dir)
        : player_state{player_ptr}
        , row_dir_{row_dir}
        , col_dir_{col_dir}
    {
    }

    void jumping_state::on_enter()
    {
        auto face_comp_ptr = player_ptr_->component<face_component>();
        face_comp_ptr->set_jump_sprite(row_dir_, col_dir_);
        auto jump_comp_ptr = player_ptr_->component<jump_component>();
        jump_comp_ptr->jump(row_dir_, col_dir_);
    }
}
