﻿#include "idle_state.h"

// Project includes
#include "component/character/direction_component.h"
#include "component/character/face_component.h"
#include "core/audio_player.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    idle_state::idle_state(mngn::game_object *character_ptr)
        : character_state{character_ptr}
    {
    }

    void idle_state::on_enter()
    {
        character_ptr_->component<face_component>()->set_sprite_orientation(2, 4, 0, 6);
        character_ptr_->component<direction_component>()->reset();

        audio_player::instance().play(audio::qbert_jump);
    }
}
