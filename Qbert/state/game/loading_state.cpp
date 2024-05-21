#include "loading_state.h"

// Project includes
#include "minigin/core/game_object.h"
#include "component/state/game_state_component.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"
#include "minigin/core/scene_manager.h"
#include "state/game/duo_state.h"
#include "state/game/solo_state.h"
#include "state/game/versus_state.h"

namespace qbert
{
    loading_state::loading_state(game_state_component* game_state_comp_ptr, int game_mode)
        : game_state{game_state_comp_ptr}
        , game_mode_{game_mode}
    {
    }

    void loading_state::on_enter()
    {
        scene_ptr_ = mngn::scene_manager::instance().find("loading");
        scene_ptr_->set_active(true);
        
        mngn::renderer::instance().set_background_color({});
    }

    void loading_state::update()
    {
        accu_time_ += mngn::game_time::instance().delta_time();
        if (accu_time_ >= loading_time_)
        {
            load_game_mode();
            accu_time_ = 0.0f;
        }
    }

    void loading_state::on_exit()
    {
        scene_ptr_->set_active(false);
    }

    void loading_state::load_game_mode()
    {
        switch (game_mode_)
        {
        case 0:
            game_state_comp_ptr_->change_state<solo_state>(game_state_comp_ptr_);
            break;
        case 1:
            game_state_comp_ptr_->change_state<duo_state>(game_state_comp_ptr_);
            break;
        case 2:
            game_state_comp_ptr_->change_state<versus_state>(game_state_comp_ptr_);
            break;
        }
    }
}
